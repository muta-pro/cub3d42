/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:35:58 by imutavdz          #+#    #+#             */
/*   Updated: 2026/02/11 11:36:28 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	init_sprite(t_game *g)
{
	g->sprite = malloc(sizeof(t_spr));
	if (!g->sprite)
		return (false);
	if (!load_spr(g))
		return (false);
	set_spr_spawn(g);
	g->sprite->curr_fr = 0;
	g->sprite->fr_tm = 0.0;
	return (true);
}
