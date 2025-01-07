/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <mregada-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:28:30 by mregada-          #+#    #+#             */
/*   Updated: 2024/12/31 13:12:20 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*ft_free(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

static char	*ft_get_line(char *next_line, char **bookmark)
{
	size_t	len_line;
	char	*extract_line;
	char	*leftovers;

	if (!next_line || !bookmark || !*bookmark)
		return (ft_free(bookmark));
	len_line = (next_line - *bookmark) + 1;
	extract_line = ft_substr(*bookmark, 0, len_line);
	if (!extract_line)
		return (NULL);
	leftovers = ft_strdup(next_line + 1);
	if (!leftovers)
		return (ft_free(&extract_line));
	ft_free(bookmark);
	*bookmark = leftovers;
	return (extract_line);
}

static ssize_t	ft_read_concat(int fd, char **bookmark, char *buffer)
{
	ssize_t	read_bytes;
	char	*temp;

	read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes < 0)
		return (-1);
	if (read_bytes >= 0)
	{
		buffer[read_bytes] = '\0';
		if (!bookmark || !*bookmark)
		{
			*bookmark = ft_strdup("");
			if (!*bookmark)
				return (-1);
		}
		temp = ft_strjoin(*bookmark, buffer);
		if (!temp)
		{
			ft_free(bookmark);
			return (-1);
		}
		ft_free(bookmark);
		*bookmark = temp;
	}
	return (read_bytes);
}

static char	*ft_read_nd_save(char **bookmark, int fd, char *buffer, char *line)
{
	ssize_t	read_bytes;
	char	*next_line;

	next_line = NULL;
	read_bytes = ft_read_concat(fd, bookmark, buffer);
	if (read_bytes < 0 && (!*bookmark || **bookmark == '\0'))
		return (ft_free(bookmark));
	while (!next_line && read_bytes > 0)
	{
		next_line = ft_strchr(*bookmark, '\n');
		if (!next_line)
			read_bytes = ft_read_concat(fd, bookmark, buffer);
	}
	if (next_line)
		line = ft_get_line(next_line, bookmark);
	else if (*bookmark && **bookmark)
	{
		line = ft_strdup(*bookmark);
		ft_free(bookmark);
	}
	else
		ft_free(bookmark);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*bookmark;
	char		*buffer;
	char		*line;
	
	//printf("Empieza gnl : fd=%d\n", fd);
	line = NULL;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
	{
		ft_free(&bookmark);
		ft_free(&buffer);
		ft_free(&line);
		return (NULL);
	}
	if (!bookmark)
		bookmark = ft_strdup("");
	line = ft_read_nd_save(&bookmark, fd, buffer, line);
	if (!line && bookmark && *bookmark == '\0')
		ft_free(&bookmark);
	ft_free(&buffer);
	//printf("Linea devuelta: %s\n", line);
	return (line);
}
