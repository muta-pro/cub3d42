/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imutavdz <imutavdz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:25:30 by imutavdz          #+#    #+#             */
/*   Updated: 2026/02/16 23:17:33 by imutavdz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_gnl
{
	int				fd;
	char			*buffer;
	struct s_gnl	*next;
}				t_gnl;

char		*get_next_line(int fd);
char		*join_buffer(char *s1, char *s2);
char		*ft_strdup(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strndup(const char *s, size_t n);
size_t		ft_strlen(const char *s);

#endif
