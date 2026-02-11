/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/05 13:31:50 by imutavdz      #+#    #+#                 */
/*   Updated: 2026/02/07 20:05:14 by imutavdz        ########   odam.nl       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//do I need free_textures()  mlx_DELETE_TEXT??

void	free_sprite(t_game *g)
{
	int	i;

	if (g->s_frames)
	{
		i = 0;
		while (i < 3)
		{
			if (g->s_frames)
				mlx_delete_texture(g->s_frames[i]);
			i++;
		}
		free(g->s_frames);
	}
	if (g->sprite)
		free(g->sprite);
}

void	free_lines(char **lines)
{
	int	i;

	i = 0;
	if (!lines)
		return ;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

void	free_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

void	print_exit(const char *errmsg, t_game *game, bool do_cleanup)
{
	if (errmsg)
	{
		ft_putstr_fd((char *)errmsg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	if (do_cleanup && game)
		final_cleanup(game);
	if (errmsg)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

void	free_tex(t_game *g)
{
	if (g->paths.no)
		free(g->paths.no);
	if (g->paths.so)
		free(g->paths.so);
	if (g->paths.we)
		free(g->paths.we);
	if (g->paths.ea)
		free(g->paths.ea);
}

void	final_cleanup(t_game *g)
{
	if (!g)
		return ;
	if (g->map.grid)
		free_grid(g->map.grid);
	// free_tex(g);
	// free_textures(g);
	free_sprite(g);
	if (g->mlx)
		mlx_terminate(g->mlx); //kills wind and img
}
