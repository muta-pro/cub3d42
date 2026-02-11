/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_str.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbagin <rbagin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/11 15:13:04 by rbagin        #+#    #+#                 */
/*   Updated: 2025/04/16 16:39:53 by rbagin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_str(char *s)
{
	if (!s)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}
