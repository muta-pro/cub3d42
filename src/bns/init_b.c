/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:35:58 by imutavdz          #+#    #+#             */
/*   Updated: 2026/02/18 01:35:41 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_door(t_game *g, int count)
{
	int	x;
	int	y;

	g->door = malloc(sizeof(t_door) * count);
	if (!g->door)
		print_exit(ERR_MEMORY, g, true);
	g->num_doors = count;
	count = 0;
	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			if (g->map.grid[y][x] == 'D')
			{
				g->door[count].x = x;
				g->door[count].y = y;
				g->door[count].open = false;
				count++;
			}
			x++;
		}
		y++;
	}
}

bool	init_sprite(t_game *g)
{
	g->sprite = malloc(sizeof(t_spr));
	if (!g->sprite)
		return (false);
	if (!load_spr(g))
		return (false);
	set_spr_spawn(g);
	g->sprite->curr_fr = 0;
	g->sprite->fr_tm = 0.0;
	return (true);
}
