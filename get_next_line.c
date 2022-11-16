/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirsella <mirsella@protonmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:54:00 by mirsella          #+#    #+#             */
/*   Updated: 2022/11/16 18:38:19 by mirsella         ###   ########.fr       */
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
	buffer[0] = '\0';
	ret = 1;
	while (ret && !ft_strchr(buffer, '\n'))
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret)
		{
			buffer[ret] = '\0';
			storage = ft_strjoin(storage, buffer);
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
	ft_strlcpy(str, storage + i, ft_strlen(storage) - i);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!storage || (storage && !ft_strchr(storage, '\n')))
		storage = read_next_line(fd, storage);
	if (!storage)
		return (NULL);
	// printf("storage: %s\n", storage);
	line = get_line_from_buffer(storage);
	tmp = get_end_of_buffer(storage);
	free(storage);
	storage = tmp;
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 
// 	fd = open("testfile", O_RDONLY);
// 	line = "";
// 	while (line)
// 	{
// 		line = get_next_line(fd);
// 		printf("line:%s\n", line);
// 		free(line);
// 	}
// }
