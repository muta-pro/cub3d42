/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 07:58:55 by imutavdz          #+#    #+#             */
/*   Updated: 2026/02/19 11:47:21 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	try_open(t_game *g)
{
	int		door_x;
	int		door_y;
	int		i;
	double	dist;

	door_x = (int)(g->player.pos.x + g->player.dir_x);
	door_y = (int)(g->player.pos.y + g->player.dir_y);
	if (is_out_of_bounds(&g->map, door_x, door_y))
		return ;
	if (g->map.grid[door_y][door_x] != 'D')
		return ;
	i = pos_door(g, door_x, door_y);
	if (i == -1)
		return ;
	dist = sqrt(pow(g->player.pos.x - door_x - 0.5, 2)
			+ pow(g->player.pos.y - door_y - 0.5, 2));
	if (dist < 1.5)
		g->door[i].open = !g->door[i].open;
}

int	pos_door(t_game *g, int x, int y)
{
	int	i;

	i = 0;
	while (i < g->num_doors)
	{
		if (g->door[i].x == x && g->door[i].y == y)
			return (i);
		i++;
	}
	return (-1);
}

static bool	open_door(t_game *g, int x, int y)
{
	int	i;

	i = pos_door(g, x, y);
	if (i == -1)
		return (false);
	return (g->door[i].open);
}

bool	hit_door(t_game *g, int x, int y)
{
	if (is_out_of_bounds(&g->map, x, y))
		return (false);
	if (g->map.grid[y][x] != 'D')
		return (false);
	return (!open_door(g, x, y));
}
