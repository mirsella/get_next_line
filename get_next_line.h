/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/spool/mail/mirsella>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:08:27 by root              #+#    #+#             */
/*   Updated: 2022/11/16 16:52:40 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "stdlib.h"
# include "unistd.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
void	*ft_memset(void *s, int c, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);

#endif