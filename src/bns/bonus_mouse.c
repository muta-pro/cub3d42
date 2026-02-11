/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 12:04:23 by imutavdz          #+#    #+#             */
/*   Updated: 2026/02/11 08:33:38 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//also fixed p->plane calc

#include "cub3d.h"

#define ROT_SPEED 3.0
#define MOUSE_S 0.0015

static void	apply_rot(t_player *p, double speed)
{
	double	old_dir_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(speed) - p->dir_y * sin(speed);
	p->dir_y = old_dir_x * sin(speed) + p->dir_y * cos(speed);
	p->plane_x = -p->dir_y * 0.66;
	p->plane_y = p->dir_x * 0.66;
}

void	rotate_mouse(t_game *game, t_player *p)
{
	int32_t	mouse_x;
	int32_t	mouse_y;
	int32_t	delta_x;

	mlx_get_mouse_pos(game->mlx, &mouse_x, &mouse_y);
	delta_x = mouse_x - (game->screen_w / 2);
	if (delta_x == 0)
		return ;
	apply_rot(p, delta_x * MOUSE_S);
	mlx_set_mouse_pos(game->mlx, game->screen_w / 2, game->screen_h / 2);
}

void	handle_rotation(t_game *game)
{
	double	speed;

	speed = ROT_SPEED * game->mlx->delta_time;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		apply_rot(&game->player, -speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		apply_rot(&game->player, speed);
	rotate_mouse(game, &game->player);
}
