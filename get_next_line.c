/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <mregada-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:28:30 by mregada-          #+#    #+#             */
/*   Updated: 2025/01/14 17:09:29 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

static char	*ft_get_line(char *nl, char **bookmark)
{
	size_t	len_line;
	char	*extract_line;
	char	*leftovers;

	if (!bookmark || !*bookmark || **bookmark == '\0')
		return (ft_free(bookmark));
	len_line = (nl - *bookmark) + 1;
	extract_line = ft_substr(*bookmark, 0, len_line);
	if (!extract_line || !nl)
		return (ft_free(bookmark));
	leftovers = ft_strdup(nl + 1);
	if (!leftovers)
	{
		ft_free(&extract_line);
		return (ft_free(bookmark));
	}
	ft_free(bookmark);
	*bookmark = leftovers;
	return (extract_line);
}

static ssize_t	ft_rejoin(int fd, char **bookmark, char *buffer, char *nl)
{
	ssize_t	read_bytes;
	char	*temp;

	read_bytes = 1;
	while (read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (-1);
		buffer[read_bytes] = '\0';
		if (!*bookmark)
		{
			*bookmark = ft_strdup("");
			if (!*bookmark)
				return (-1);
		}
		temp = ft_strjoin(*bookmark, buffer);
		ft_free(bookmark);
		*bookmark = temp;
		nl = ft_strchr(*bookmark, '\n');
		if (nl)
			break ;
	}
	return (read_bytes);
}

static char	*ft_read_nd_save(char **bookmark, int fd, char *buffer, char *line)
{
	ssize_t	read_bytes;
	char	*nl;

	nl = NULL;
	read_bytes = ft_rejoin(fd, bookmark, buffer, nl);
	if (read_bytes < 0)
		return (ft_free(bookmark));
	nl = ft_strchr(*bookmark, '\n');
	if (nl)
		line = ft_get_line(nl, bookmark);
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

	line = NULL;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, buffer, 0) < 0 || !buffer)
	{
		ft_free(&bookmark);
		return (ft_free(&buffer));
	}
	line = ft_read_nd_save(&bookmark, fd, buffer, line);
	ft_free(&buffer);
	return (line);
}
