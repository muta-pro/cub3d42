/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/23 16:29:24 by imutavdz      #+#    #+#                 */
/*   Updated: 2026/02/07 20:26:06 by imutavdz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MAX_MAP_H 2000
#define MAX_MAP_W 2000

//Map validation (flood fill to ensure walls surround player)
//no holes in the wall
//player can't wak out of bounds
static bool	is_walkable(char c)
{
	return (c == 'W' || c == 'N' || c == 'E' || c == 'S' || c == 'D' || c == '0');
}

void	flfill_pl_pos(t_game *g, int x, int y, bool **checked)
{
	char	c;

	if (x < 0 || y < 0 || x > g->map.width || y > g->map.height)
		print_exit(ERR_MAP_WALLS, g, true);
	if (checked[y][x])
		return ;
	c = g->map.grid[y][x];
	if (c == '1')
		return ;
	if (c == ' ')
		print_exit(ERR_MAP_WALLS, g, true);
	if (is_walkable(c))
	{
		checked[y][x] = true;
		flfill_pl_pos(g, x + 1, y, checked); //r
		flfill_pl_pos(g, x - 1, y, checked); //l
		flfill_pl_pos(g, x, y + 1, checked); //d
		flfill_pl_pos(g, x, y - 1, checked); //u
	}
}

static bool	check_map_size(t_game *g)
{
	if (g->map.height > MAX_MAP_H || g->map.width > MAX_MAP_W)
		return (print_exit(ERR_MAP_SZ, g, true), false);
	if (g->map.height < 3 || g->map.width < 3)
		return (print_exit(ERR_MAP_SZ, g, true), false);
	return (true);
}

void	valid_map(t_game *g)
{
	bool	**checked;
	int		y;

	check_map_size(g);
	checked = malloc(sizeof(bool *) * g->map.height);
	if (!checked)
		print_exit(ERR_MEMORY, g, true);
	y = 0;
	while (y < g->map.height)
	{
		checked[y] = ft_calloc(g->map.width, sizeof(bool));
		if (!checked[y])
			print_exit(ERR_MEMORY, g, true);
		y++;
	}
	flfill_pl_pos(g, (int)g->player.pos.x, (int)g->player.pos.y, checked);
	y = 0;
	while (y < g->map.height)
	{
		free(checked[y]);
		y++;
	}
	free(checked);
}
