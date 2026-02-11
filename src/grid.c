/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   grid.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/06 17:31:24 by imutavdz      #+#    #+#                 */
/*   Updated: 2026/02/07 20:06:19 by imutavdz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//Calculate height and max width of map
//calc_dim_map exits on blank lines, but the subject allows trailing empty 
//lines after the map—you should stop at first blank after map start

static void	calc_dim_map(char **lines, int m_start, t_game *g)
{
	int		height;
	int		max_width;
	int		len;

	height = 0;
	max_width = 0;
	while (lines[m_start + height])
	{
		if (is_blank_line(lines[m_start + height]))
			break ; // Don't error yet. Valid will handle if map is too small.
		if (!is_map_line(lines[m_start + height]))
			print_exit(ERR_MAP_LN, g, true);
		len = ft_strlen(lines[m_start + height]); //do we need int cast?
		if (len > max_width)
			max_width = len;
		height++;
	}
	if (height == 0 || max_width == 0)
		print_exit(ERR_MAP_EMPTY, g, true);
	g->map.height = height;
	g->map.width = max_width;
}

//handles the horisontal chars in a row

static void	fill_row(char *grid_row, char *line, int w)
{
	int	x;

	x = 0;
	while (x < w) // Fill width with spaces (default for short lines)
	{
		grid_row[x] = ' ';
		x++;
	}
	grid_row[x] = '\0';
	x = 0; // overwrite start row with actual line content
	while (line[x] && x < w)
	{
		grid_row[x] = line[x];
		x++;
	}
}
//Convert map lines to rectangular 2D grid
//handles vertical rows
//Returns: Allocated 2D char array (rectangular, space-padded)

static char	**create_grid(char **lines, int m_start, t_game *g)
{
	int		y;
	char	**grid;

	grid = malloc(sizeof(char *) * (g->map.height + 1));
	if (!grid)
		print_exit(ERR_MEMORY, g, true);
	y = 0;
	while (y < g->map.height)
	{
		grid[y] = malloc(g->map.width + 1); //alloc row
		if (!grid[y])
		{
			grid[y] = NULL; //nul term for partial cleanup
			print_exit(ERR_MEMORY, g, true);
		}
		fill_row(grid[y], lines[m_start + y], g->map.width); //pass specif row and src line
		y++;
	}
	grid[y] = NULL;
	return (grid);
}
//Parse map section into 2D grid
//init alloc

void	parse_map_grid(char **lines, int map_start, t_game *g)
{
	calc_dim_map(lines, map_start, g);
	g->map.grid = create_grid(lines, map_start, g);
}
