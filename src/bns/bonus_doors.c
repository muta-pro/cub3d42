/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_doors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 13:58:40 by imutavdz          #+#    #+#             */
/*   Updated: 2026/02/19 07:47:30 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_door(t_game *g)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			if (g->map.grid[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	if (count == 0)
		return ;
	init_door(g, count);
}
