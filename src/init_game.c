/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:27:57 by imutavdz          #+#    #+#             */
/*   Updated: 2026/02/11 11:17:41 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init(game->screen_w, game->screen_h, "cub3D", false);
	if (!game->mlx)
		return (print_exit(ERR_MLX, game, true), 1);
	game->frame = mlx_new_image(game->mlx, game->screen_w, game->screen_h);
	if (!game->frame)
		return (print_exit(ERR_MLX, game, true), 1);
	game->img_mini = mlx_new_image(game->mlx, MINI_W, MINI_H);
	if (!game->img_mini)
		return (print_exit(ERR_MLX, game, true), 1);
	return (0);
}

void	init_minimap(t_game *g)
{
	g->mini_tile_sz = MINI_TL_SZ;
	g->mini_view_range = MINI_VIEW_RANGE;
	g->img_mini = mlx_new_image(g->mlx, MINI_W, MINI_H);
	if (!g->img_mini)
	{
		print_exit(ERR_MLX, g, true);
		return ;
	}
	if (mlx_image_to_window(g->mlx, g->img_mini, 10, 10) < 0)
	{
		print_exit(ERR_MLX, g, true);
		return ;
	}//layer priority
	g->img_mini->instances[0].z = 100; //high z value (ONTOP)
}
