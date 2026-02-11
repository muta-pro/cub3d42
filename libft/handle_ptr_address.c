/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_ptr_address.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbagin <rbagin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/11 15:25:32 by rbagin        #+#    #+#                 */
/*   Updated: 2025/04/16 16:40:01 by rbagin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_ptraddress(char *buffer, int i)
{
	int	length;

	length = 2;
	while (buffer[i])
	{
		ft_putchar_fd(buffer[i], 1);
		length++;
		i++;
	}
	return (length);
}

int	handle_ptraddress(uintptr_t add)
{
	char	buffer[20];
	int		i;
	int		digit;

	if (!add)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	buffer[16] = '\0';
	i = 15;
	while (add > 0)
	{
		digit = add % 16;
		if (digit < 10)
			buffer[i] = '0' + digit;
		else
			buffer[i] = 'a' + (digit - 10);
		add /= 16;
		i--;
	}
	i++;
	ft_putstr_fd("0x", 1);
	return (print_ptraddress(buffer, i));
}
