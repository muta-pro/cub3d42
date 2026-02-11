/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:44:27 by imutavdz          #+#    #+#             */
/*   Updated: 2026/02/10 14:52:35 by imutavdz         ###   ########.fr       */
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
	line = malloc(len + 1);
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
//Split file content by newlines into array of strings
//Each line is a separate allocated string.
//Returns: NULL-terminated array of strings, or exits on error
//lines = alloc array of str pointers
// Handle last line if no trailing newline

char	**split_lines(char *file_str, t_game *g)
{
	char		**lines;
	int			line_count;
	int			i;
	const char	*start;
	const char	*curr;

	if (!file_str)
		print_exit(ERR_MEMORY, g, false);
	line_count = count_lines(file_str);
	if (line_count == 0)
		print_exit(ERR_MAP_EMPTY, g, false);
	lines = malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
		print_exit(ERR_MEMORY, g, false);
	i = 0;
	start = file_str;
	curr = file_str;
	while (*curr)
	{
		if (*curr == '\n')
		{
			lines[i] = extract_line(start, curr);
			if (!lines[i])
				print_exit(ERR_MEMORY, g, true);
			i++;
			start = curr + 1;
		}
		curr++;
	}
	if (start < curr && *(curr - 1) != '\n')
	{
		lines[i] = extract_line(start, curr);
		if (!lines[i])
			print_exit(ERR_MEMORY, g, true);
		i++;
	}
	lines[i] = NULL;
	return (lines);
}
