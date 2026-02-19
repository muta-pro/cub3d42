/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbagin <rbagin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/28 12:43:35 by rbagin        #+#    #+#                 */
/*   Updated: 2026/02/02 21:04:24 by rbagin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray_delta(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

static void	init_ray_step(t_player *player, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1 - player->pos.x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1 - player->pos.y) * ray->delta_dist_y;
	}
}

static void	perform_dda(t_game *g, t_ray *ray)
{
	ray->hit = false;
	while (ray->hit == false)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (hit_wall_or_bounds(&g->map, ray->map_x, ray->map_y))
			ray->hit = true;
		else if (hit_door(g, ray->map_x, ray->map_y))
			ray->hit = true;
	}
}

void	calc_perp_dist(t_player *player, t_ray *ray)
{
	if (ray->side == 0)
	{
		ray->perp_wall_dist = (ray->map_x - player->pos.x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	}
	else
	{
		ray->perp_wall_dist = (ray->map_y - player->pos.y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
	}
}

void	cast_ray(t_player *player, t_game *g, t_ray *ray)
{
	ray->map_x = floor(player->pos.x);
	ray->map_y = floor(player->pos.y);
	init_ray_delta(ray);
	init_ray_step(player, ray);
	perform_dda(g, ray);
	calc_perp_dist(player, ray);
}
