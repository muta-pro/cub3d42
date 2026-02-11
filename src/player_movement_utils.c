/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbagin <rbagin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/05 10:25:28 by rbagin        #+#    #+#                 */
/*   Updated: 2026/02/06 20:33:56 by rbagin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define COLISION_MAR 0.05

void	try_move(t_game *game, t_player *player, double dx, double dy)
{
	double	new_pos_x;
	double	new_pos_y;

	new_pos_x = player->pos.x + dx;
	new_pos_y = player->pos.y + dy;
	if (is_valid_position(game, new_pos_x, new_pos_y))
	{
		player->pos.x = new_pos_x;
		player->pos.y = new_pos_y;
		return ;
	}
	if (is_valid_position(game, new_pos_x, player->pos.y))
		player->pos.x = new_pos_x;
	if (is_valid_position(game, player->pos.x, new_pos_y))
		player->pos.y = new_pos_y;
}

static bool	is_wall(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return (true);
	return (map->grid[y][x] == '1' || map->grid[y][x] == ' ');
}

bool	is_valid_position(t_game *game, double x, double y)
{
	t_map	*map;

	map = &game->map;
	if (is_wall(map, (int)(x - COLISION_MAR), (int)(y - COLISION_MAR)))
		return (false);
	if (is_wall(map, (int)(x + COLISION_MAR), (int)(y - COLISION_MAR)))
		return (false);
	if (is_wall(map, (int)(x - COLISION_MAR), (int)(y + COLISION_MAR)))
		return (false);
	if (is_wall(map, (int)(x + COLISION_MAR), (int)(y + COLISION_MAR)))
		return (false);
	return (true);
}
