/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirsella <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:54:00 by mirsella          #+#    #+#             */
/*   Updated: 2022/11/17 15:59:04 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_next_line(int fd, char *storage)
{
	char	*buffer;
	int		ret;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	ret = 1;
	while (ret > 0 && !ft_strchr(buffer, '\n'))
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret > 0)
		{
			buffer[ret] = '\0';
			storage = ft_s1join(storage, buffer);
		}
	}
	free(buffer);
	if (ret == -1)
		return (NULL);
	return (storage);
}

char	*get_line_from_buffer(char *storage)
{
	char	*str;
	int		i;

	i = 0;
	if (!storage[0])
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, storage, i + 1);
	return (str);
}

char	*get_end_of_buffer(char *storage)
{
	char	*str;
	int		i;

	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\0')
		return (NULL);
	i++;
	str = malloc(sizeof(char) * (ft_strlen(storage) - i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, storage + i, ft_strlen(storage) - i + 1);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*tmp;
	static char	*storage[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	if (!storage[fd] || (storage[fd] && !ft_strchr(storage[fd], '\n')))
		storage[fd] = read_next_line(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	line = get_line_from_buffer(storage[fd]);
	tmp = get_end_of_buffer(storage[fd]);
	free(storage[fd]);
	storage[fd] = tmp;
	return (line);
}
