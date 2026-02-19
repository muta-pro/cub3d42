/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: imutavdz <imutavdz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/23 16:29:24 by imutavdz      #+#    #+#                 */
/*   Updated: 2026/02/07 20:26:06 by imutavdz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_g_struct(t_game *g)
{
	ft_bzero(g, sizeof(*g));
	g->screen_w = SCREEN_WIDTH;
	g->screen_h = SCREEN_HEIGHT;
	g->player.last_mouse_x = SCREEN_WIDTH / 2;
	g->mini_tile_sz = MINI_TL_SZ;
	g->mini_view_range = MINI_VIEW_RANGE;
	g->show_minimap = true;
	// g->m_key_pressed = false;
}

int	main(int argc, char const *argv[])
{
	t_game	game;

	if (argc != 2)
		return (print_exit(ERR_ARGS, NULL, false), 1);
	init_g_struct(&game);
	load_map(&game, argv[1]); //exit inside func
	valid_map(&game);
	init_mlx(&game);
	if (!load_textures(&game))
		return (print_exit(ERR_TEX_LOAD, &game, true), 1);
	if (mlx_image_to_window(game.mlx, game.frame, 0, 0) < 0)
		return (print_exit(ERR_MLX, &game, true), 1);
	if (mlx_image_to_window(game.mlx, game.img_mini, 0, 0) < 0)
		return (print_exit(ERR_MLX, &game, true), 1);
	if (!init_sprite(&game))
		return (print_exit(ERR_SPR_INIT, &game, true), 1);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	final_cleanup(&game); //kills grid and paths
	return (0);
}
