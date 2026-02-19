/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:43:09 by imutavdz          #+#    #+#             */
/*   Updated: 2026/02/18 02:27:25 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//Check if line contains only whitespace
bool	is_blank_line(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (false);
		line++;
	}
	return (true);
}
//Check if line is part of the map grid
//check if there is a map returned
//Map lines start with '1', '0', or ' ' (after trimming leading whitespace)

bool	is_map_line(const char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (*line == '1' || *line == '0' || *line == ' ');
}

bool	is_out_of_bounds(t_map *map, int x, int y)
{
	return (x < 0 || x >= map->width || y < 0 || y >= map->height);
}

bool	hit_wall_or_bounds(t_map *map, int x, int y)
{
	if (is_out_of_bounds(map, x, y))
		return (true);
	return (map->grid[y][x] == '1');
}

bool	is_inside(t_game *g, int x, int y)
{
	if (x >= 0 && x < (int)g->img_mini->width
		&& y >= 0 && y < (int)g->img_mini->height)
		return (true);
	return (false);
}
