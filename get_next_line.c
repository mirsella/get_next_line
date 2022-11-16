/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirsella <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:54:00 by mirsella          #+#    #+#             */
/*   Updated: 2022/11/16 17:21:35 by mirsella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_next_line(int fd, char *storage)
{
	char	*buffer;
	int		ret;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	ft_memset(buffer, 0, BUFFER_SIZE + 1);
	ret = 1;
	while (ret && !ft_strchr(buffer, '\n'))
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret > 0)
		{
			buffer[ret] = '\0';
			ft_strjoin(storage, buffer);
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
	int	i;
	
	i = 0;
	while (storage[i] || storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, storage, i);
	return (str);
}

// char	*get_end_of_buffer(char *storage)
// {
// }

char	*get_next_line(int fd)
{
	static char	*storage;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!storage || (storage && !ft_strchr(storage, '\n')))
	{
		storage = read_next_line(fd, storage);
	}
	if (!storage)
		return (NULL);
	line = get_line_from_buffer(storage);
	// storage = get_end_of_buffer(storage);
	return (line);
}

#include "stdio.h"
#include "fcntl.h"
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("testfile", O_RDONLY);
	line = "";
	while (line)
	{
		line = get_next_line(fd);
		printf("%s\n", line);
	}
	return (0);
}
