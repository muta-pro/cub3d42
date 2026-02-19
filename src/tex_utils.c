/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tex_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/05 13:31:50 by imutavdz      #+#    #+#                 */
/*   Updated: 2026/02/07 20:05:14 by imutavdz        ########   odam.nl       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//grabs pxl using 0.0 to 1.0 % coordinate

uint32_t	sample_texture(xpm_t *xpm, double tex_x, double tex_y)
{
	int		x;
	int		y;
	uint8_t	*p;

	if (!xpm)
		return (0); //multipl % by actual text dim
	x = (int)(tex_x * (double)xpm->texture.width);
	y = (int)(tex_y * (double)xpm->texture.height);
	if (x < 0)
		x = 0;
	if (x >= (int)xpm->texture.width)
		x = (int)xpm->texture.width - 1;
	if (x < 0)
		y = 0;
	if (y >= (int)xpm->texture.height)
		y = (int)xpm->texture.height -1;
	p = &xpm->texture.pixels[(y * xpm->texture.width + x) * 4];
	return ((p[0] << 24 | p[1] << 16 | p[2] << 8) | p[3]);
}

//returns mlx text pointer based on wall face

xpm_t	*get_text(t_game *g, t_ray *ray)
{
	if (g->map.grid[ray->map_y][ray->map_x] == 'D')
		return (g->tex[TEX_D].xpm);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		return (g->tex[TEX_W].xpm);
	if (ray->side == 0)
		return (g->tex[TEX_E].xpm);
	if (ray->ray_dir_y > 0)
		return (g->tex[TEX_N].xpm);
	return (g->tex[TEX_S].xpm);
}
//check flipping and fetches color

uint32_t	get_color(t_game *g, t_ray *ray, double tex_y)
{
	xpm_t	*xpm;
	double	tex_x;

	xpm = get_text(g, ray);
	if (!xpm)
		return (FALLBACK);
	tex_x = ray->wall_x; //flip text pervent mirroring
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = 1.0 - tex_x;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = 1.0 - tex_x;
	return (sample_texture(xpm, tex_x, tex_y));
}

bool	load_one_t(t_game *g, int id, char *path)
{
	g->tex[id].xpm = mlx_load_xpm42(path);
	if (!g->tex[id].xpm)
		print_exit(ERR_TEX_LOAD, g, true);
	g->tex[id].width = g->tex[id].xpm->texture.width;
	g->tex[id].height = g->tex[id].xpm->texture.height;
	return (true);
}
