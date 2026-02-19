/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   macro.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/23 16:22:59 by imutavdz      #+#    #+#                 */
/*   Updated: 2026/02/06 20:07:36 by rbagin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

//error messages
# define ERR_ARGS "Error\nIncorrect number of arguments"
# define ERR_HEAD_CH "Error\nIncorrect identifier in header"
# define ERR_MAP_CHARS "Error\nInvalid characters in map"
# define ERR_MISS_COLOR "Error\nMissing color"
# define ERR_COLOR_FORM "Error\nWrong color format"
# define ERR_DUPL "Error\nInvalid duplicates"
# define ERR_MAP_EMPTY_LN "Error\nEmpty lines inside map"
# define ERR_MAP_LN "Error\nInvalid map line"
# define ERR_MAP_SPAWN "Error\nMap must contain exactly one spawn"
# define ERR_MAP_RECT "Error\nMap is not rectangular"
# define ERR_MAP_WALLS "Error\nMap is not surrounded by walls"
# define ERR_MAP_EXT "Error\nMap file must have .cub extension"
# define ERR_MAP_OPEN "Error\nCould not open map file"
# define ERR_MEMORY "Error\nMemory allocation failed"
# define ERR_MLX "Error\nMLX initialization failed"
# define ERR_MAP_EMPTY "Error\nMAP file is invalid"
# define ERR_MAP_SZ "Error\nMAP size invalid"
# define ERR_NO_TEX_ID "Error\nTexture identifier not present"
# define ERR_TEX_PATH "Error\nNo texture path"
# define ERR_TEX_LOAD "Error\nFailed texture loading"
# define ERR_SPR_INIT "Error\nFailed sprite initialization"
//.cub identifiers
# define NO "NO"
# define SO "SO"
# define EA "EA"
# define WE "WE"
# define F "F"
# define C "C"

# define PLAYER_N 'N'
# define PLAYER_S 'S'
# define PLAYER_W 'W'
# define PLAYER_E 'E'

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define FOV_SCALE 66
//minimap size
# ifndef MINI_TL_SZ
# define MINI_TL_SZ 20
 #endif
# ifndef MINI_VIEW_RANGE
# define MINI_VIEW_RANGE 15
# endif
//210pxl
# ifndef MINI_H
# define MINI_H ((MINI_VIEW_RANGE * 2 + 1) * MINI_TL_SZ)
# endif
# ifndef MINI_W
# define MINI_W ((MINI_VIEW_RANGE * 2 + 1) * MINI_TL_SZ)
# endif

# define RED_DOT 0xFF0000FF
# define SPR_DOT 0x00FF00FF
# define MINI_WALL 0xFFFFFF80
# define WALK_TRNS 0x20FF0060
# define MINI_EMPTY 0x00800030
# define DIR_RAY 0x00FF00FF
# define FALLBACK 0xFF00FFFF


# define CREATE_RGB(r, g, b) ((r) << 16 | (g) << 8 | (b))
//delete these after adding textures.
# define N_COLOR CREATE_RGB(167, 17, 17)
# define S_COLOR CREATE_RGB(26, 214, 26)
# define E_COLOR CREATE_RGB(2, 47, 226)
# define W_COLOR CREATE_RGB(192, 244, 5)

# endif
