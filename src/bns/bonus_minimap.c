/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:19:07 by imutavdz          #+#    #+#             */
/*   Updated: 2026/02/11 17:16:56 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	tile_color(t_game *g, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= g->map.width
		|| map_y < 0 || map_y >= g->map.height)
		return (MINI_EMPTY);
	if (g->map.grid[map_y][map_x] == '1')
		return (MINI_WALL);
	if (g->map.grid[map_y][map_x] == '0')
		return (WALK_TRNS);
	return (MINI_EMPTY);
}

static void	draw_tile(t_game *g, int screen_x, int screen_y, uint32_t color)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->mini_tile_sz)
	{
		x = 0;
		while (x < g->mini_tile_sz)
		{
			if (screen_x + x >= 0 && screen_x + x < (int)g->img_mini->width
				&& screen_y + y >= 0 && screen_y + y < (int)g->img_mini->height)
				mlx_put_pixel(g->img_mini, screen_x + x, screen_y + y, color);
			x++;
		}
		y++;
	}
}

static void	draw_all_tiles(t_game *g)
{
	t_mini	mmap;

	mmap.tile_y = -g->mini_view_range;
	while (mmap.tile_y <= g->mini_view_range)
	{
		mmap.tile_x = -g->mini_view_range;
		while (mmap.tile_x <= g->mini_view_range)
		{//map coordinates from tile coord
			mmap.map_x = (int)g->player.pos.x + mmap.tile_x;
			mmap.map_y = (int)g->player.pos.y + mmap.tile_y;
			//screen coord from tile coord
			mmap.screen_x = (mmap.tile_x + g->mini_view_range)
				* g->mini_tile_sz;
			mmap.screen_y = (mmap.tile_y + g->mini_view_range)
				* g->mini_tile_sz;
			mmap.color = tile_color(g, mmap.map_x, mmap.map_y);
			draw_tile(g, mmap.screen_x, mmap.screen_y, mmap.color);
			mmap.tile_x++;
		}
		mmap.tile_y++;
	}
}

static void	draw_dot(t_game *g, int c_x, int c_y)
{
	int	x;
	int	y;
	int	size;

	size = 15;
	y = -size / 2;
	while (y <= size / 2)
	{
		x = -size / 2;
		while (x <= size / 2)
		{
			if (c_x + x >= 0 && c_x + x < (int)g->img_mini->width
				&& c_y + y >= 0 && c_y + y < (int)g->img_mini->height)
				mlx_put_pixel(g->img_mini, c_x + x, c_y + y, RED_DOT);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *g)
{
	int		center_x;
	int		center_y;

	ft_bzero(g->img_mini->pixels,
		g->img_mini->width * g->img_mini->height * sizeof(uint32_t));
	draw_all_tiles(g);
	center_x = g->mini_view_range * g->mini_tile_sz + (g->mini_tile_sz / 2);
	center_y = g->mini_view_range * g->mini_tile_sz + (g->mini_tile_sz / 2);
	draw_dot(g, center_x, center_y);
	draw_mini_spr(g);
	calc_dir_line(g, center_x, center_y);
}
