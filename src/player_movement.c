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
void	move_forward(t_game *game, t_player *player)
{
	double	dx;
	double	dy;

	dx = player->dir_x * SPEED * game->mlx->delta_time;
	dy = player->dir_y * SPEED * game->mlx->delta_time;
	try_move(game, player, dx, dy);
}

void	move_backward(t_game *game, t_player *player)
{
	double	dx;
	double	dy;

	dx = -player->dir_x * SPEED * game->mlx->delta_time;
	dy = -player->dir_y * SPEED * game->mlx->delta_time;
	try_move(game, player, dx, dy);
}

void	move_left(t_game *game, t_player *player)
{
	double	dx;
	double	dy;

	dx = player->dir_y * SPEED * game->mlx->delta_time;
	dy = -player->dir_x * SPEED * game->mlx->delta_time;
	try_move(game, player, dx, dy);
}

void	move_right(t_game *game, t_player *player)
{
	double	dx;
	double	dy;

	dx = -player->dir_y * SPEED * game->mlx->delta_time;
	dy = player->dir_x * SPEED * game->mlx->delta_time;
	try_move(game, player, dx, dy);
}

void	handle_movement(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward(game, &game->player);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_backward(game, &game->player);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left(game, &game->player);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_right(game, &game->player);
}
