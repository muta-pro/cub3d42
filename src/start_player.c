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

static void	set_orientation(t_player *p, char orient)
{
	const t_orient	table[4] = {
	{'N', 0.0, -1.0, 0.66, 0.0},
	{'S', 0.0, 1.0, -0.66, 0.0},
	{'E', 1.0, 0.0, 0.0, 0.66},
	{'W', -1.0, 0.0, 0.0, -0.66}
	};
	int				i;

	i = 0;
	while (i < 4)
	{
		if (table[i].c == orient)
		{
			p->dir_x = table[i].dir_x;
			p->dir_y = table[i].dir_y;
			p->plane_x = table[i].plane_x;
			p->plane_y = table[i].plane_y;
			return ;
		}
		i++;
	}
}

void	init_player(t_player *p, char orient, int x, int y)
{
	p->pos.x = x + 0.5;
	p->pos.y = y + 0.5;
	set_orientation(p, orient);
}

static int	valid_ch(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == '1' || c == '0' || c == ' ' || c == 'D');
}

static void	consume_spawn(t_game *g, int x, int y, int *count)
{
	int	c;

	c = g->map.grid[y][x];
	(*count)++;
	init_player(&g->player, c, x, y);
	g->map.grid[y][x] = '0';
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
			if (!valid_ch(c))
				print_exit(ERR_MAP_CHARS, g, true);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				consume_spawn(g, x, y, &count);
			x++;
		}
		y++;
	}
	if (count != 1)
		print_exit(ERR_MAP_SPAWN, g, true);
}
