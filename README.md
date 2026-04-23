# cub3D — A Vector-Based Raycasting Engine

---

## What This Is!


cub3D is a first-person 3D engine built from scratch in C, using nothing but raycasting mathematics and a minimal graphics library (MLX42). No OpenGL. No game engine. No hand-holding. Just math, pointers, and the grim satisfaction of watching something render correctly after hours of debugging floating-point arithmetic.

This was built as part of the 42 School curriculum. The mandatory part implements a functional raycasting engine. The bonus part adds interactive doors, a player-centric minimap, and animated sprites — because apparently suffering is additive.

If you're looking for Unity or Unreal, you've come to the wrong place. This is C. We do things properly here.

## FLOW-CHART display -> [Cub3d](https://github.com/user-attachments/assets/cb531bfc-f809-4b17-b07c-0231ea3ce724)

---

## The Architecture: Don't Feed Garbage to the Engine

A rendering engine is only as fast and stable as the data you feed it. The parsing pipeline is strictly linear and validates everything before the engine ever touches a single pixel.

| Stage | Function | Purpose |
|-------|----------|---------|
| I/O | `read_file()` | Reads the entire `.cub` file into memory via `get_next_line()` |
| Tokenization | `split_lines()` | Converts the raw buffer into a workable array of strings |
| Header Parsing | `parse_header()` | Extracts and validates textures (NO/SO/WE/EA) and RGB colors (F/C) |
| Grid Generation | `parse_map_grid()` | Allocates the strictly validated 2D character array |
| Flood Fill | `valid_map()` | Confirms the map is fully enclosed — before anything renders |
| Spawn Init | `find_spawn()` | Sets `player.pos`, `player.dir_xy`, and FOV via `player.plane_xy` |
| Door Init | `find_door()` | Scans the grid and allocates door state array (bonus) |

If the map is broken, the program dies here. We don't wait for a segmentation fault in the render loop.

---

## The Engine: Vectors and Linear Algebra

The core rendering loop fires one ray per screen column. It doesn't use slow angle-stepping or expensive trigonometry per ray — it uses strict vector mathematics.

### DDA (Digital Differential Analysis)

For each ray, we calculate the distance to the next X and Y grid line intersection (`delta_dist_x`, `delta_dist_y`). The DDA loop then steps through the 2D map array mathematically, advancing whichever axis is closer. This guarantees we never miss a wall intersection, no matter how shallow the angle.

### Perpendicular Distance (No Fisheye)

Raw Euclidean distance from player to wall hit causes fisheye distortion. Instead, we project the hit distance back onto the camera plane using vector projection (`perp_wall_dist`). The result is geometrically correct perspective with zero distortion.

---

## Texture Mapping: Sub-Pixel Accuracy

Once a wall is hit, we compute exactly where the ray intersected the tile to determine the correct texture column.

**Horizontal (X-axis):** The decimal part of the hit coordinate (`ray->wall_x`) maps to a pixel column on the texture. Hitting a wall at 0.75 means drawing the 48th column of a 64px-wide texture.

**Vertical (Y-axis):** A step value derived from the projected wall height interpolates down the texture vertically, pulling the correct pixel row for every screen row in the strip.

**Endian-Safe Pixel Reading:** Rather than casting raw pixel arrays to 32-bit integers (which flips ABGR on little-endian machines), we read exactly 4 `uint8_t` bytes from the `.xpm42` texture buffer and manually shift them into our RGBA format. Pixel-perfect on any architecture.

---

## Color Packing: Bitwise Operations

We don't carry around bloated structs with separate `r`, `g`, `b` integers for floor and ceiling colors. During parsing, RGB strings are validated against the 0–255 boundary and packed immediately into a single 32-bit integer using bitwise shifts:

```c
color = (r << 16) | (g << 8) | b;
```

The rendering loop deals with a single cache-friendly primitive when painting the upper and lower halves of the screen. No structs. No overhead.

---

## The Minimap: Done Right (Bonus)

The naive minimap iterates the entire `map.grid` every frame. That is wasteful and it scales terribly.

This engine implements a **player-centric minimap** with three core properties:

**World-to-Screen Translation:** The player stays dead center. The world translates around them based on relative map offsets — no camera panning, no coordinate remapping every frame.

**Viewport Clipping:** Rendering coordinates are strictly clamped to the minimap boundaries. Any pixel outside the view window is dropped before it's drawn.

**Constant-Cost Culling:** A bounding box defined by `mini_view_range` limits iteration to only the tiles visible in the minimap. Whether the map is 10×10 or 1000×1000, the draw cost is fixed. That's O(1) with respect to total map size.

### Normalized Vectors for the Direction Line

The direction indicator doesn't call `cos()` or `sin()` every frame. Because the engine uses normalized direction vectors, their magnitude is always exactly 1.0:

$$\sqrt{dir\_x^2 + dir\_y^2} = 1.0$$

Drawing a 15-pixel direction line is just `dir_x * 15`, `dir_y * 15`. The line length never drifts as the player rotates because the ratio between X and Y shifts perfectly while magnitude stays mathematically constant.

Press `M` to toggle the minimap.

---

## Camera Rotation: Decoupled Mouse Look

Keyboard turning is archaic. The engine traps the mouse, hides the system cursor via `mlx_set_cursor_mode`, and tracks the delta from center each frame. That delta drives a 2D rotation matrix applied to both the direction vector and the camera plane:

```c
old_dir_x = dir_x;
dir_x = dir_x * cos(rot_speed) - dir_y * sin(rot_speed);
dir_y = old_dir_x * sin(rot_speed) + dir_y * cos(rot_speed);
plane_x = -dir_y * 0.66;
plane_y =  dir_x * 0.66;
```

The camera plane is recalculated explicitly after every rotation rather than relying on floating-point accumulation to stay perpendicular over time. Because it won't. It never does.

---

## Sprite Rendering: Camera-Space Projection & Z-Buffering (Bonus)

Drawing a sprite isn't slapping a PNG on the screen. It requires transforming world coordinates into the player's local camera space.

**Inverse Camera Matrix:** The relative vector from player to sprite is multiplied by the inverse of the 2D camera matrix (defined by `dir` and `plane`). This yields the sprite's depth and lateral screen position.

**Perspective Divide:** The lateral position is divided by depth to scale the sprite dynamically as it approaches the camera.

**1D Z-Buffer:** The raycasting loop populates a per-column array of perpendicular wall distances. Before drawing each vertical stripe of a sprite, we do an O(1) lookup. If the sprite's depth exceeds the Z-buffer value at that column, it's behind a wall — pixel dropped.

**Delta-Time Animation:** Frame transitions are driven by `mlx->delta_time`, not CPU cycles. Animations run at exactly the same speed on a 60Hz monitor as on a 240Hz one.

---

## Interactive Doors (Bonus)

The map grid isn't a static array of `1`s and `0`s. It supports dynamic state.

`D` tiles are doors. The DDA loop checks door state before treating a tile as a wall hit — a closed door reflects the ray; an open door lets it through. Collision detection does the same check, so the player is physically blocked by closed doors and can walk through open ones.

Press `X` while facing a door within range to toggle it. Door tiles can have their own texture via the `DO` identifier in the map header, or fall back to the west wall texture if none is provided. Freeing is guarded to prevent double-free on the shared pointer.

---

## Map Format

```
NO ./textures/north.xpm42
SO ./textures/south.xpm42
WE ./textures/west.xpm42
EA ./textures/east.xpm42
DO ./textures/door.xpm42    # optional, bonus only

F 50,50,50
C 30,30,80

111111111
100000001
100D00001
100000001
10000N001
111111111
```

Valid map characters: `1` (wall), `0` (floor), `D` (door), `N/S/E/W` (player spawn + facing direction). The map must be fully enclosed by walls. Exactly one spawn point is required. If the map has holes, the flood-fill validator catches it before anything renders.

---

## Build & Run

**Requirements:** `cc`, `make`, `glfw3`

```bash
# Install GLFW if needed
brew install glfw          # macOS
apt install libglfw3-dev   # Linux

# Clone with submodules
git clone 
cd cub3D

# Mandatory
make
./cub3D maps/your_map.cub

# Bonus (doors, minimap, sprites)
make bonus
./cub3D_bonus maps/your_map.cub
```

The engine compiles with `-Wall -Wextra -Werror` — if it doesn't compile cleanly, it's broken. `-ffast-math` accelerates the floating-point trigonometry in the rotation and sprite projection paths.

---

## Controls

| Key | Action |
|-----|--------|
| `W A S D` | Move (wall-sliding collision) |
| `← →` or Mouse | Rotate camera |
| `X` | Open / close door |
| `M` | Toggle minimap |
| `ESC` | Quit cleanly |

---

## Authors

Built by **imutavdz** and **rbagin** at 42 School / Codam.

The engine works. The code is clean. The walls don't bleed through. That's enough.

---
