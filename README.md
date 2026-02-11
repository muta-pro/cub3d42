Project: This project implements a vector-based ray-casting engine to visualise a maze from a first-person perspective, using linear algebra, trigonometry, and real-time rendering techniques in C - developed by imutavdz and rbagin:

+++ Description:

a ray-casting engine

using 2D vectors + linear algebra + trigonometry

to create a pseudo-3D first-person perspective

rendered in real time using MLX42

Engine: 
represents the player view with direction and camera plane vectors

casts one ray vector per screen column

computes intersections using vector stepping (DDA)

projects wall height using perpendicular distance (vector projection)

maps texture coordinates using vector math.

+++ Code Architecture flow:

- Parsing:
----------------------------------------------------+
	provides:
1 - player.pos -> start of the rays (tile center)
2 - player.dir_xy -> facing idrection
3 - player.plane_xy -> camera plane (FOV)
4 - map.grid -> walkable/wall data
--------------------------------------------------- +
open_map_file() 
  ↓
read_entire_file()    ← get_next_line() loop
  ↓													+
split_lines()         ← convert to array
  ↓
parse_header()        ← extract NO/SO/WE/EA/F/C 	+
  ↓
validate_identifiers() 								+
  ↓
parse_map_grid()      ← create 2D char array 		+
  ↓
find_player_spawn()   ← locate N/S/E/W 				+
----------------------------------------------------+