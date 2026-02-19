/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:44:27 by imutavdz          #+#    #+#             */
/*   Updated: 2026/02/17 12:17:46 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//where and when do I free this line??
#include "cub3d.h"
//count_lines - Count number of lines in string
//str: Newline-separated string
// If string doesn't end with newline, we have one more line
//Returns: Number of lines (counts newlines + 1 if no trailing newline)
static int	count_lines(const char *str)
{
	int	count;

	count = 0;
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			count++;
		str++;
	}
	if (*(str - 1) != '\n')
		count++;
	return (count);
}
//Extract one line from position, allocate and copy it
//End of line (points to '\n' or '\0')
// Allocated string containing the line (without '\n'), or NULL on error

static char	*extract_line(const char *start, const char *end)
{
	char	*line;
	size_t	len;
	size_t	i;

	len = end - start;
	line = malloc(len + 1); //should I free a line here? or is it handeled in load_map?
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = start[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static bool	store_line(char **lines, int *i, const char *start, const char *end)
{
	lines[*i] = extract_line(start, end);
	if (!lines[*i])
		return (false);
	(*i)++;
	return (true);
}

static void	fill_lines(char **lines, char *file_str, t_game *g)
{
	int			i;
	const char	*start;
	const char	*curr;

	start = file_str;
	curr = file_str;
	i = 0;
	while (*curr)
	{
		if (*curr == '\n')
		{
			if (!store_line(lines, &i, start, curr))
				print_exit(ERR_MEMORY, g, true);
			start = curr + 1;
		}
		curr++;
	}
	if (start < curr && *(curr - 1) != '\n')
	{
		if (!store_line(lines, &i, start, curr))
			print_exit(ERR_MEMORY, g, true);
	}
	lines[i] = NULL;
}

//Split file content by newlines into array of strings
//Each line is a separate allocated string.
//Returns: NULL-terminated array of strings, or exits on error
//lines = alloc array of str pointers
// Handle last line if no trailing newline

char	**split_lines(char *file_str, t_game *g)
{
	char		**lines;
	int			line_count;

	if (!file_str)
		print_exit(ERR_MEMORY, g, false);
	line_count = count_lines(file_str);
	if (line_count == 0)
		print_exit(ERR_MAP_EMPTY, g, false);
	lines = malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
		print_exit(ERR_MEMORY, g, false);
	fill_lines(lines, file_str, g);
	return (lines);
}
