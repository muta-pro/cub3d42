/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 17:26:31 by imutavdz          #+#    #+#             */
/*   Updated: 2026/02/16 21:27:00 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Output value (0-255)
static bool	parse_single_value(const char *str, int *value, char **next)
{
	int	result;
	int	digits;

	result = 0;
	digits = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		digits++;
		str++;
		if (result > 255)
			return (false);
	}
	if (digits == 0)
		return (false);
	*value = result;
	*next = (char *)str;
	return (true);
}
//Parse "R,G,B" format into packed integer
//out_color: Output color in format 0x00RRGGBB
//s: String containing "R,G,B" (e.g., "255,100,0")

static bool	comma_next(const char **next)
{
	while (**next == ' ' || **next == '\t')
		(*next)++;
	if (**next != ',')
		return (false);
	(*next)++;
	return (true);
}

bool	parse_rgb(const char *s, int *out_color)
{
	int		r;
	int		g;
	int		b;
	char	*next;

	if (!s || !out_color)
		return (false);
	if (!parse_single_value(s, &r, &next))
		return (false);
	comma_next((const char **)&next);
	if (!parse_single_value(next, &g, &next))
		return (false);
	comma_next((const char **)&next);
	if (!parse_single_value(next, &b, &next))
		return (false);
	while (*next == ' ' || *next == '\t' || *next == '\n' || *next == '\r')
		next++;
	if (*next != '\0')
		return (false);
	*out_color = (r << 16) | (g << 8) | b;
	return (true);
}
