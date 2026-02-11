/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_player.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/25 17:43:33 by imutavdz      #+#    #+#                 */
/*   Updated: 2026/02/06 19:55:48 by imutavdz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*(For colors, best is to add flags later: bool has_floor; bool has_ceiling;)*/

#include "cub3d.h"

void	init_player(t_game *g, char orient, int x, int y)
{
	g->player.pos.x = x + 0.5;
	g->player.pos.y = y + 0.5;
	if (orient == 'N')
	{
		g->player.dir_x = 0.0;
		g->player.dir_y = -1.0;
		g->player.plane_x = 0.66;
		g->player.plane_y = 0.0;
	}
	else if (orient == 'S')
	{
		g->player.dir_x = 0.0;
		g->player.dir_y = 1.0;
		g->player.plane_x = -0.66;
		g->player.plane_y = 0.0;
	}
	else if (orient == 'E')
	{
		g->player.dir_x = 1.0;
		g->player.dir_y = 0.0;
		g->player.plane_x = 0.0;
		g->player.plane_y = 0.66;
	}
	else if (orient == 'W')
	{
		g->player.dir_x = -1.0;
		g->player.dir_y = 0.0;
		g->player.plane_x = 0.0;
		g->player.plane_y = -0.66;
	}
}

void	find_spawn(t_game *g)
{
	int		count;
	int		y;
	int		x;
	char	c;

	count = 0;
	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			c = g->map.grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				count++;
				init_player(g, c, x, y);
				g->map.grid[y][x] = '0';
			}
			else if (c == '0' || c == '1' || c == ' ')
			{
				//valid map char
			}
			else
				print_exit(ERR_MAP_CHARS, g, true);
			x++;
		}
		y++;
	}
	if (count != 1)
		print_exit(ERR_MAP_SPAWN, g, true);
}
