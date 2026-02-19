/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbagin <rbagin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/02 20:54:03 by rbagin        #+#    #+#                 */
/*   Updated: 2026/02/06 19:43:02 by imutavdz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//changed bc must used parsed colors
//conver parsed rgb to rgba

static void	draw_ceiling_floor(t_game *game, int x, t_ray *ray)
{
	int			y;
	uint32_t	floor_rgba;
	uint32_t	ceiling_rgba;

	floor_rgba = ((uint32_t)game->color.floor << 8) | 0xFF;
	ceiling_rgba = ((uint32_t)game->color.ceiling << 8) | 0xFF;
	y = 0;
	while (y < ray->draw_start)
	{
		mlx_put_pixel(game->frame, x, y, ceiling_rgba);
		y++;
	}
	y = ray->draw_end;
	while (y < game->screen_h)
	{
		mlx_put_pixel(game->frame, x, y, floor_rgba);
		y++;
	}
}
//this one should be modified for textures

void	draw_vertical_line(t_game *g, int x, t_ray *ray)
{
	uint32_t	color;
	int			y;
	double		tex_y;

	draw_ceiling_floor(g, x, ray);
	if (ray->side == 0) //calc where ray hit on wall exact decimal 0.0.-1.0
		ray->wall_x = g->player.pos.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = g->player.pos.x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x); //strip int part
	y = ray->draw_start;
	while (y < ray->draw_end)
	{//how far are we down the text
		tex_y = (y - g->screen_h / 2.0 + ray->line_height / 2.0)
			/ (double)ray->line_height;
		color = get_color(g, ray, tex_y);
		mlx_put_pixel(g->frame, x, y, color);
		y++;
	}
}

static void	calc_line_height(t_game *g, t_ray *ray)
{
	ray->line_height = (int)(g->screen_h / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + g->screen_h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + g->screen_h / 2;
	if (ray->draw_end >= g->screen_h)
		ray->draw_end = g->screen_h -1;
}

static void	init_ray_dir(t_game *g, t_player *player, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)g->screen_w - 1;
	ray->ray_dir_x = player->dir_x + (player->plane_x * ray->camera_x);
	ray->ray_dir_y = player->dir_y + (player->plane_y * ray->camera_x);
}

void	render_scene(t_game *game, t_player *player, t_ray *ray)
{
	int	x;

	x = 0;
	while (x < game->screen_w)
	{
		init_ray_dir(game, player, ray, x);
		cast_ray(player, game, ray);
		calc_line_height(game, ray);
		draw_vertical_line(game, x, ray);
		game->z_buff[x] = ray->perp_wall_dist;
		x++;
	}
}
