/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbagin <rbagin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/02/05 19:09:52 by rbagin        #+#    #+#                 */
/*   Updated: 2026/02/08 19:23:00 by imuatvdz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Texture loading (load .png files into memory)

static bool	load_n_tex(t_game *g)
{
	return (load_one_t(g, TEX_N, g->paths.no));
}

static bool	load_s_tex(t_game *g)
{
	return (load_one_t(g, TEX_S, g->paths.so));
}

static bool	load_w_tex(t_game *g)
{
	return (load_one_t(g, TEX_W, g->paths.we));
}

static bool	load_e_tex(t_game *g)
{
	return (load_one_t(g, TEX_E, g->paths.ea));
}

bool	load_textures(t_game *g)
{
	if (!load_n_tex(g))
		return (false);
	if (!load_s_tex(g))
		return (false);
	if (!load_w_tex(g))
		return (false);
	if (!load_e_tex(g))
		return (false);
	return (true);
}
