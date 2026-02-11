/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: yneshev <yneshev@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 17:33:17 by yneshev       #+#    #+#                 */
/*   Updated: 2024/10/24 16:34:54 by yneshev       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_lst)
{
	if (!new_lst && !lst)
		return ;
	new_lst->next = *lst;
	*lst = new_lst;
}
