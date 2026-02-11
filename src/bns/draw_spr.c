/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_spr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 19:05:26 by imutavdz          #+#    #+#             */
/*   Updated: 2026/02/11 11:35:38 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	calc_tex_x(t_spr *s, int screen_x, int spr_screenx)
{
	return ((screen_x - (-s->spr_w / 2 + spr_screenx))
		* s->spr_tex->width / s->spr_w);
}
//multiply by 4, each pxl takse 4 bytes RGBA

static uint32_t	get_spr_pxl(t_spr *s, int tex_x, int tex_y)
{
	uint8_t		*pixels;
	int			indx;
	uint32_t	color;

	if (tex_x < 0 || tex_x >= (int)s->spr_tex->width
		|| tex_y < 0 || tex_y >= (int)s->spr_tex->height)
		return (0); //calc byte idx in 1d array
	indx = (tex_y * s->spr_tex->width + tex_x) * 4;
	pixels = &s->spr_tex->pixels[indx];
	color = (pixels[0] << 24) | (pixels[1] << 16)
		| (pixels[2] << 8) | pixels[3];
	return (color);
}

static bool	check_zbuff(t_game *g, t_spr *s, int x)
{
	return (s->spr_y > 0 && x >= 0
		&& x < g->screen_w && s->spr_y < g->z_buff[x]);
}

static void	draw_stripe_spr(t_game *g, t_spr *s, int x, int tex_x)
{
	double		step;
	double		tex_pos;
	int			y;
	uint32_t	color;

	step = (double)s->spr_tex->height / s->spr_h;
	tex_pos = (s->drw_starty - (-s->spr_h / 2 + g->screen_h / 2)) * step;
	y = s->drw_starty;
	while (y < s->drw_endy)
	{
		color = get_spr_pxl(s, tex_x, (int)tex_pos);
		if ((color & 0x000000FF) != 0)
			mlx_put_pixel(g->frame, x, y, color);
		tex_pos += step;
		y++;
	}
}
//logic of two loops:
//horisontal = which col x im drawing
//vertical = for this col x, draw a stripe of pxls from top to bottom

void	draw_sprite(t_game *g, t_spr *s, int spr_screenx)
{
	int			x;
	int			tex_x;

	x = s->drw_startx;
	while (x < s->drw_endx)
	{
		if (check_zbuff(g, s, x))
		{
			tex_x = calc_tex_x(s, x, spr_screenx);
			draw_stripe_spr(g, s, x, tex_x);
		}
		x++;
	}
}
