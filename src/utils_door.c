/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 07:58:55 by imutavdz          #+#    #+#             */
/*   Updated: 2026/02/19 08:04:41 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
