/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/25 17:42:59 by imutavdz      #+#    #+#                 */
/*   Updated: 2026/02/09 20:07:21 by imutavdz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* if no map:
If it finishes the loop without returning 
(meaning it never found a line starting with 1, 0, or ),
it calls print_exit(ERR_MAP_EMPTY).*/
#include "cub3d.h"
//Parse color identifier line (F/C)
bool	parse_color_line(const char *line, t_game *g)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (parse_rgb(line + 2, &g->color.floor))
			return (g->color.f_set = true, true);
		return (false);
	}
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (parse_rgb(line + 2, &g->color.ceiling))
			return (g->color.c_set = true, true);
		return (false);
	}
	return (false);
}
//Set texture path, ensure no duplicates
//path_ptr: Source path string (after identifier)

bool	set_tex_path(char **dst, const char *path_pt)
{
	char	*trim;

	if (*dst != NULL)
		return (false);
	trim = ft_strtrim(path_pt, " \t\n\r");
	if (!trim)
		return (false);
	if (trim[0] == '\0')
	{
		free(trim);
		return (false);
	}
	*dst = trim;
	return (true);
}
//Parse texture identifier line (NO/SO/WE/EA)

bool	parse_tex_line(const char *line, t_game *g)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (set_tex_path(&g->paths.no, line + 3));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (set_tex_path(&g->paths.so, line + 3));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (set_tex_path(&g->paths.we, line + 3));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (set_tex_path(&g->paths.ea, line + 3));
	return (false);
}
//Parse header section (textures and colors)
//Processes lines until map starts.
//Returns: Index where map begins, or exits on error

int	parse_header(char **lines, t_game *g)
{
	int	i;

	i = 0; //can iterate wuth a pointer instead
	while (lines[i])
	{
		if (is_blank_line(lines[i]))
		{
			i++;
			continue ;
		}
		if (is_map_line(lines[i]))
			return (i);
		if (parse_tex_line(lines[i], g) || parse_color_line(lines[i], g))
		{
			i++;
			continue ;
		}
		print_exit(ERR_MAP_CHARS, g, true);
	}
	print_exit(ERR_MAP_EMPTY, g, true);
	return (-1);
}
