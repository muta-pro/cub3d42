/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ravi-bagin <ravi-bagin@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/03 13:13:21 by ravi-bagin    #+#    #+#                 */
/*   Updated: 2026/02/08 20:31:50 by imutavdz    ########   odam.nl           */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define SPEED 2
//check first diagonal (no jitter)
//if diagonal failed - slide along wall.
static void	calculate_forward_backward(t_game *game, double *dx, double *dy)
{
	t_player	*player;
	double		speed_delta;

	player = &game->player;
	speed_delta = SPEED * game->mlx->delta_time;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		*dx += player->dir_x * speed_delta;
		*dy += player->dir_y * speed_delta;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		*dx -= player->dir_x * speed_delta;
		*dy -= player->dir_y * speed_delta;
	}
}

static void	calculate_strafe(t_game *game, double *dx, double *dy)
{
	t_player	*player;
	double		speed_delta;

	player = &game->player;
	speed_delta = SPEED * game->mlx->delta_time;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		*dx += player->dir_y * speed_delta;
		*dy -= player->dir_x * speed_delta;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		*dx -= player->dir_y * speed_delta;
		*dy += player->dir_x * speed_delta;
	}
}

void	handle_movement(t_game *game)
{
	double	dx;
	double	dy;

	dx = 0.0;
	dy = 0.0;
	calculate_forward_backward(game, &dx, &dy);
	calculate_strafe(game, &dx, &dy);
	if (dx != 0.0 || dy != 0.0)
		try_move(game, &game->player, dx, dy);
}
