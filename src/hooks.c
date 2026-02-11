/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:51:43 by imutavdz          #+#    #+#             */
/*   Updated: 2026/02/11 10:49:59 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_loop(void *param)
{
	t_game			*g;
	t_ray			ray;

	g = (t_game *)param;
	handle_movement(g);
	handle_rotation(g);
	if (g->sprite)
		update_sprite(g);
	ft_bzero(g->frame->pixels, g->screen_w * g->screen_h * sizeof(uint32_t));
	render_scene(g, &g->player, &ray);
	if (g->sprite)
		render_sprite(g, g->sprite);
	if (g->show_minimap == true)
		draw_minimap(g);
}

static void	key_press(mlx_key_data_t keydata, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(g->mlx);
		//toggle minimap with M
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
	{
		g->show_minimap = !g->show_minimap;
		if (g->img_mini && g->img_mini->count > 0)
			g->img_mini->instances[0].enabled = g->show_minimap;
	}
}
//register all hooks
//init mouse position for rotation

void	setup_hooks(t_game *g)
{
	mlx_key_hook(g->mlx, &key_press, g);
	mlx_loop_hook(g->mlx, &game_loop, g);
	g->player.last_mouse_x = g->screen_w / 2;
	mlx_set_cursor_mode(g->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(g->mlx, g->screen_w / 2, g->screen_h / 2);
}
