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

//Map validation (flood fill to ensure walls surround player)
//no holes in the wall
//player can't wak out of bounds

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
	if (c == '0')
	{
		checked[y][x] = true;
		flfill_pl_pos(g, x + 1, y, checked); //r
		flfill_pl_pos(g, x - 1, y, checked); //l
		flfill_pl_pos(g, x, y + 1, checked); //d
		flfill_pl_pos(g, x, y - 1, checked); //u
	}
}

void	valid_map(t_game *g)
{
	bool	**checked;
	int		y;

	checked = malloc(sizeof(bool *) * g->map.height);
	if (!checked)
		print_exit(ERR_MEMORY, g, true);
	y = 0;
	while (y < g->map.height)
	{
		checked[y] = ft_calloc(g->map.width, sizeof(bool));
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
