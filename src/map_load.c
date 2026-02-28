/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_load.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/25 17:43:12 by imutavdz      #+#    #+#                 */
/*   Updated: 2026/02/07 19:32:47 by imutavdz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*read_file(int fd, t_game *g)
{
	char	*line;
	char	*full_str;
	char	*store;

	full_str = ft_strdup("");
	if (!full_str)
		print_exit(ERR_MEMORY, g, false);
	line = get_next_line(fd);
	while (line)
	{
		store = ft_strjoin(full_str, line);
		free(full_str);
		free(line);
		if (!store)
			print_exit(ERR_MEMORY, g, false);
		full_str = store;
		line = get_next_line(fd);
	}
	if (ft_strlen(full_str) == 0)
	{
		free(full_str);
		print_exit(ERR_MAP_EMPTY, g, false);
	}
	return (full_str);
}

static bool	valid_filname(const char *filename) //different input
{
	char	*dot;

	if (!filename)
		return (false);
	dot = ft_strrchr(filename, '.');
	if (!dot)
		return (false);
	if (ft_strncmp(dot, ".cub", 5) == 0)
		return (true);
	return (false);
}

static int	open_map(const char *name, t_game *g)
{
	int	fd;

	if (!valid_filname(name))
		print_exit(ERR_MAP_EXT, g, false);
	fd = open(name, O_RDONLY);
	if (fd < 0)
		print_exit(ERR_MAP_OPEN, g, false);
	return (fd);
}

bool	load_map(t_game *g, const char *filename)
{
	int		fd;
	char	*content;
	int		map_start;

	fd = open_map(filename, g);
	content = read_file(fd, g);
	close(fd);
	g->lines = split_lines(content, g);
	free(content);
	map_start = parse_header(g->lines, g);
	parse_map_grid(g->lines, map_start, g);
	find_spawn(g);
	free_lines(g->lines);
	g->lines = NULL;
	find_door(g);
	return (true);
}
