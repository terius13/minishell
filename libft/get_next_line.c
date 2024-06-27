/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:18:22 by ting              #+#    #+#             */
/*   Updated: 2024/06/27 20:53:19 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_buffer(int *bytesread, int fd, char *wholebuff)
{
	char	*buffer;
	char	*temp;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, BUFFER_SIZE + 1);
	if (!wholebuff)
	{
		wholebuff = (char *)malloc(BUFFER_SIZE + 1);
		ft_bzero(wholebuff, BUFFER_SIZE + 1);
	}
	*bytesread = read(fd, buffer, BUFFER_SIZE);
	temp = wholebuff;
	wholebuff = ft_strcat(temp, buffer, ft_strlen(buffer));
	free(temp);
	free(buffer);
	if (*bytesread < 0 || (!*bytesread && !*wholebuff))
	{
		free(wholebuff);
		wholebuff = NULL;
	}
	return (wholebuff);
}

static char	*next_line(char *wholebuff)
{
	char	*line;
	int		len;
	char	*ptr;

	len = 0;
	while (wholebuff[len] != '\n')
		len++;
	len++;
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	ft_bzero(line, len);
	ptr = line;
	line = ft_strcat(ptr, wholebuff, len);
	free(ptr);
	return (line);
}

static char	*removeline(char *wholebuff)
{
	int		len;
	char	*ptr;

	len = 0;
	while (wholebuff[len] != '\n')
		len++;
	len++;
	ptr = wholebuff;
	wholebuff = ft_strdup(ft_strchr(wholebuff, '\n') + 1);
	free(ptr);
	if (wholebuff[0] == '\0')
	{
		free(wholebuff);
		wholebuff = NULL;
	}
	return (wholebuff);
}

char	*get_next_line(int fd)
{
	static char	*wholebuff;
	char		*line;
	int			bytesread;

	bytesread = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (ft_strchr(wholebuff, '\n') == NULL && bytesread)
	{
		wholebuff = get_buffer(&bytesread, fd, wholebuff);
		if (!wholebuff)
			break ;
	}
	if (ft_strchr(wholebuff, '\n') != NULL)
	{
		line = next_line(wholebuff);
		wholebuff = removeline(wholebuff);
		return (line);
	}
	if (!wholebuff)
		return (NULL);
	line = ft_strdup(wholebuff);
	free(wholebuff);
	wholebuff = NULL;
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>
int     main(void)
{
        char    *line;
        int fd = open("test.txt", O_RDONLY);

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	free(line);
	close(fd);
        return (0);
}
*/
