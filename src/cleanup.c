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

void	final_cleanup(t_game *g)
{
	if (!g)
		return ;
	if (g->map.grid)
		free_grid(g->map.grid);
	free_tex(g);
	free_textures(g);
	free_sprite(g);
	if (g->mlx)
		mlx_terminate(g->mlx); //kills wind and img
}
