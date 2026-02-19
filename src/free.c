/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:07:48 by imutavdz          #+#    #+#             */
/*   Updated: 2026/02/19 07:42:04 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (g->paths.d)
		free(g->paths.d);
}

void	free_textures(t_game *g)
{
	if (g->tex[TEX_N].xpm)
	{
		mlx_delete_xpm42(g->tex[TEX_N].xpm);
		g->tex[TEX_N].xpm = NULL;
	}
	if (g->tex[TEX_S].xpm)
	{
		mlx_delete_xpm42(g->tex[TEX_S].xpm);
		g->tex[TEX_S].xpm = NULL;
	}
	if (g->tex[TEX_W].xpm)
	{
		mlx_delete_xpm42(g->tex[TEX_W].xpm);
		g->tex[TEX_W].xpm = NULL;
	}
	if (g->tex[TEX_E].xpm)
	{
		mlx_delete_xpm42(g->tex[TEX_E].xpm);
		g->tex[TEX_E].xpm = NULL;
	}
	if (g->tex[TEX_D].xpm && g->paths.d)
	{
		mlx_delete_xpm42(g->tex[TEX_D].xpm);
		g->tex[TEX_D].xpm = NULL;
	}
}
