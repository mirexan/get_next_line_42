/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <mregada-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:47:15 by mregada-          #+#    #+#             */
/*   Updated: 2024/12/28 15:23:12 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	while (str[counter] != '\0')
		counter++;
	return (counter);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*resultado;
	size_t	len;
	size_t	len2;

	len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	resultado = (char *)malloc(sizeof(char) * len);
	if (resultado == NULL)
		return (NULL);
	len = 0;
	len2 = 0;
	while (s1[len] != '\0')
	{
		resultado[len] = s1[len];
		len++;
	}
	while (s2[len2] != '\0')
	{
		resultado[len + len2] = s2[len2];
		len2++;
	}
	resultado[len + len2] = '\0';
	return (resultado);
}

char	*ft_strdup(char	*src)
{
	size_t		len;
	char		*copia;
	size_t		i;

	len = 0;
	i = 0;
	while (src[len] != '\0')
		len++;
	copia = malloc(len + 1);
	if (copia == NULL)
		return (NULL);
	while (i < len)
	{
		copia[i] = src[i];
		i++;
	}
	copia[len] = '\0';
	return (copia);
}

char	*ft_strchr(const char *str, int c)
{
	size_t			i;
	unsigned char	uc;

	uc = (unsigned char)c;
	i = 0;
	while (str[i] != '\0')
	{
		if ((unsigned char)str[i] == uc)
			return ((char *)&str[i]);
		i++;
	}
	if (uc == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*resultado;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	resultado = (char *) malloc((len + 1) * sizeof(char));
	if (resultado == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start] != '\0')
	{
		resultado[i] = s[start];
		start++;
		i++;
	}
	resultado[i] = '\0';
	return (resultado);
}
