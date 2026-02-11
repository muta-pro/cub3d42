/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 09:39:53 by imutavdz          #+#    #+#             */
/*   Updated: 2026/02/11 11:36:12 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_spr_spawn(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			if (g->map.grid[y][x] == '0'
				&& (x != (int)g->player.pos.x || y != (int)g->player.pos.y))
			{
				g->sprite->x = x + 0.5;
				g->sprite->y = y + 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
	g->sprite->x = g->player.pos.x;
	g->sprite->y = g->player.pos.y;
}

bool	load_spr(t_game *g)
{
	int		i;
	char	*paths[4];

	paths[0] = "textures/left.png";
	paths[1] = "textures/front.png";
	paths[2] = "textures/right.png";
	paths[3] = "textures/front.png";
	g->sprite->num_fr = 4; //alloc arr 3 frames
	g->sprite->fr_durat = 0.1;
	g->s_frames = malloc(sizeof(mlx_texture_t *) * 4);
	if (!g->s_frames)
		return (false);
	i = 0;
	while (i < 4)
	{
		g->s_frames[i] = mlx_load_png(paths[i]);
		if (!g->s_frames[i])
			print_exit(ERR_TEX_LOAD, g, true);
		i++;
	}
	return (true);
}

static void	trnsf_pos_to_camera(t_game *g, t_spr *s, double *sp_x, double *sp_y)
{
	double	inv_det;
	double	transf_x;
	double	transf_y;

	*sp_x = s->x - g->player.pos.x;
	*sp_y = s->y - g->player.pos.y;
	inv_det = 1.0 / (g->player.plane_x * g->player.dir_y
			-g->player.dir_x * g->player.plane_y);
	transf_x = inv_det * (g->player.dir_y * (*sp_x)
			-g->player.dir_x * (*sp_y));
	transf_y = inv_det * (-g->player.plane_y * (*sp_x)
			+ g->player.plane_x * (*sp_y));
	*sp_x = transf_x;
	*sp_y = transf_y;
}

void	render_sprite(t_game *g, t_spr *s)
{
	int	spr_screenx;

	s->spr_tex = g->s_frames[s->curr_fr];
	trnsf_pos_to_camera(g, s, &s->spr_x, &s->spr_y);
	if (s->spr_y <= 0)
		return ;
	spr_screenx = (int)((g->screen_w / 2) * (1 + s->spr_x / s->spr_y));
	s->spr_h = abs((int)(g->screen_h / s->spr_y) / 2);
	s->spr_w = s->spr_h;
	s->drw_starty = -s->spr_h / 2 + g->screen_h / 2;
	if (s->drw_starty < 0)
		s->drw_starty = 0;
	s->drw_endy = s->spr_h / 2 + g->screen_h / 2;
	if (s->drw_endy >= g->screen_h)
		s->drw_endy = g->screen_h - 1;
	s->drw_startx = -s->spr_w / 2 + spr_screenx;
	if (s->drw_startx < 0)
		s->drw_startx = 0;
	s->drw_endx = s->spr_w / 2 + spr_screenx;
	if (s->drw_endx >= g->screen_w)
		s->drw_endx = g->screen_w - 1;
	if (s->drw_startx < s->drw_endx && s->drw_starty < s->drw_endy)
		draw_sprite(g, s, spr_screenx);
}

void	update_sprite(t_game *g)
{
	t_spr	*s;
	double	delta_time;

	s = g->sprite;
	delta_time = g->mlx->delta_time;
	if (s->num_fr <= 1)
		return ;
	s->fr_tm += delta_time;
	if (s->fr_tm >= s->fr_durat)
	{
		s->fr_tm = 0.0;
		s->curr_fr++;
		if (s->curr_fr >= s->num_fr)
			s->curr_fr = 0;
	}
}
