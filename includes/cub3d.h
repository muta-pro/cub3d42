/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbagin <rbagin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/14 18:14:26 by rbagin        #+#    #+#                 */
/*   Updated: 2026/02/10 19:42:00 by imutavdz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <MLX42/MLX42.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <math.h>
# include "libft.h"
# include "gnl.h"
# include "macro.h"

typedef	struct s_game t_game;

typedef struct s_pos
{
	double	x;	// position on the map
	double	y;
}	t_pos;

typedef struct s_player
{
	t_pos	pos;
	double	dir_x;	// direction on the map
	double	dir_y;
	double	plane_x;	// Camera plane(perpendicular(90 degrees) to dir)
	double	plane_y;
	int32_t	last_mouse_x;
}			t_player;

typedef struct s_spr
{
	double			x;
	double			y;
	int				screen_x;
	int				screen_y;
	int				curr_fr;
	double			fr_tm;
	double			fr_durat;
	int				num_fr;
	mlx_texture_t	*spr_tex;
	int				drw_startx;
	int				drw_endx;
	int				drw_starty;
	int				drw_endy;
	int				spr_h;
	int				spr_w;
	double 			spr_x;
	double 			spr_y;
}	t_spr;

typedef	struct s_ray
{
	double	camera_x;	// x coordinate on camera plane (-1 to 1)
	double	ray_dir_x;	// ray direction vector x
	double	ray_dir_y;	// ray direction vector y

	int		map_x;		// current map square
	int		map_y;

	double	side_dist_x;	// distance from current position to next x gridline
	double	side_dist_y;	// distance from current position to next y gridline

	double	delta_dist_x;	// distance ray travels between x gridlines
	double	delta_dist_y;	// distance ray travels between y gridlines

	int		step_x;	//step direction in x (1 or -1)
	int		step_y;	//step direction in x (1 or -1)

	bool	hit;
	int		side;	// 0 = x side || 1 = y side

	double	perp_wall_dist;	// perpendicular(90 degrees) distance to wall
	int		line_height;		// height of wall line to draw
	int		draw_start;			// lowest pixel to draw
	int		draw_end;			// highest pixel to draw
	double	wall_x;
	int		tex_x;
}			t_ray;

typedef	struct	s_map
{
	char	**grid;		//2D array representing the map
	int		width;
	int		height;
} 	t_map;

typedef enum e_side
{
	TEX_N = 0,
	TEX_S = 1,
	TEX_W = 2,
	TEX_E = 3
}	t_side;

typedef struct s_tex_path
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}			t_texpath;

typedef struct s_color
{
	int		floor;
	int		ceiling;
	bool	f_set;
	bool	c_set;
}			t_color;

typedef struct s_texset
{
	xpm_t			*xpm;
	int				width;
	int				height;
}			t_texset;

typedef struct s_mini
{
	int			tile_x;
	int			tile_y;
	int			map_x;
	int			map_y;
	int			screen_x;
	int			screen_y;
	int			end_x;
	int			end_y;
	uint32_t	color;
	int			size;
	t_game		*g;
}	t_mini;

typedef	struct	s_game
{
	mlx_t			*mlx;
	mlx_image_t		*frame;
	t_player		player;
	t_map			map;
	t_color			color;
	t_texpath		paths;
	t_texset		tex[4];
	int				screen_w;
	int				screen_h;
	mlx_image_t		*img_mini;
	bool			show_minimap;
	bool			m_key_pressed;
	int				mini_tile_sz;
	int				mini_view_range;
	mlx_texture_t	**s_frames;
	t_spr			*sprite;
	double			z_buff[SCREEN_WIDTH];
}	t_game;

static inline uint32_t	rgb_to_rgba(int rgb)
{
	return ((uint32_t)rgb << 8 | 0xFF);
}

//start
int				init_mlx(t_game *game);
void			game_loop(void *param);
bool			load_textures(t_game *g);
void			init_minimap(t_game *g);
bool			init_sprite(t_game *g);
bool			load_spr(t_game *g);
void			set_spr_spawn(t_game *g);
//rgb.c
bool			parse_rgb(const char *s, int *out_color);

//cleanup.c
void			print_exit(const char *errmsg, t_game *game, bool do_cleanup);
void			free_lines(char **lines);
void			free_grid(char **grid);
void			final_cleanup(t_game *g);
void			free_textures(t_game *g);

//parsing map
bool			load_map(t_game *g, const char *filename);
bool			is_blank_line(const char *line);
bool			is_map_line(const char *line);
int				parse_header(char **lines, t_game *g);
char			**split_lines(char *file_str, t_game *g);
void			parse_map_grid(char **lines, int map_start, t_game *game);
void			find_spawn(t_game *g);
void			valid_map(t_game *g);
bool			is_inside(t_game *g, int x, int y);

//raycasting
void			cast_ray(t_player *player, t_map *map, t_ray *ray);

//render
void			render_scene(t_game *game, t_player *player, t_ray *ray);
uint32_t		get_wall_color(t_ray *ray);
void			draw_vertical_line(t_game *game, int x, t_ray *ray);
bool			load_one_t(t_game *g, int id, char *path);
void			draw_minimap(t_game *g);
void			draw_sprite(t_game *g, t_spr *s, int spr_screenx);
void			draw_mini_spr(t_game *g);
void			render_sprite(t_game *g, t_spr *s);
uint32_t		sample_texture(xpm_t *xpm, double tex_x, double tex_y);
xpm_t			*get_text(t_game *g, t_ray *ray);
uint32_t		get_color(t_game *g, t_ray *ray, double tex_y);

//player_movement
void			setup_hooks(t_game *game);
void			handle_movement(t_game *game);
bool			is_valid_position(t_game *game, double x, double y);
void			try_move(t_game *game, t_player *player, double dx, double dy);

//player_rotation
void			handle_rotation(t_game *game);

void			calc_dir_line(t_game *g, int center_x, int center_y);
void			update_sprite(t_game *g);

#endif
