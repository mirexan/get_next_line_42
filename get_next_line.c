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

	if (!bookmark || !*bookmark || **bookmark == '\0')//20. Si el bookmark es inválido o está vacío, libera memoria y retorna NULL.
		return (ft_free(bookmark));
	len_line = (nl - *bookmark) + 1;//21. Longitud desde inicio hasta '\n'.
	extract_line = ft_substr(*bookmark, 0, len_line);//22. Crea una copia de la línea (incluyendo '\n' si lo hay).
	if (!extract_line || !nl) //23. si falla la asignacion
		return (ft_free(bookmark));
	leftovers = ft_strdup(nl + 1);//24. Crea una copia de lo que queda después de '\n'.
	if (!leftovers)//25. si falla asignacion
	{
		ft_free(&extract_line);
		return (ft_free(bookmark));
	}
	ft_free(bookmark);//26. liberamos bookmark viejo
	*bookmark = leftovers;//27. copiamos el resto del bookmark
	return (extract_line);
}

static ssize_t	ft_rejoin(int fd, char **bookmark, char *buffer, char *nl)
{
	ssize_t	read_bytes;
	char	*temp;

	read_bytes = 1; //7. inicio para entrar en el bucle
	while (read_bytes != 0)//8. cuando read devuelve 0 es que ya no hay nada que leer
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);//9. lee lo que hay se asigna en fd devuelve bytes leidos segun buffer_size y los almacena en buffer
		if (read_bytes < 0)//10. manejo de error de lectura
			return (-1);
		buffer[read_bytes] = '\0';//11. para que el join detecte final de str
		if (!*bookmark)//12. Si no hay contenido en bookmark, inicializa como una cadena vacía.
		{
			*bookmark = ft_strdup("");
			if (!*bookmark)
				return (-1);
		}
		temp = ft_strjoin(*bookmark, buffer);//13. Combinar lo leido con bookmark
		ft_free(bookmark); //14. liberamos lo anterior
		*bookmark = temp;//15. le ponemos a bookmark lo combinado
		nl = ft_strchr(*bookmark, '\n');//16. si lo que hay en bookmark tiene un \n salimos del bucle
		if (nl)
			break ;
	}
	return (read_bytes);//17. Devuelve los bytes leídos (0 si fin de archivo)
}

static char	*ft_read_nd_save(char **bookmark, int fd, char *buffer, char *line)
{
	ssize_t	read_bytes;
	char	*nl;

	nl = NULL;
	read_bytes = ft_rejoin(fd, bookmark, buffer, nl);//6. junta buffer a bookmark, busca lineas
	if (read_bytes < 0)
		return (ft_free(bookmark));
	nl = ft_strchr(*bookmark, '\n');//18. situar el punto donde se extrae la linea
	if (nl)
		line = ft_get_line(nl, bookmark);//19. extrae linea
	else if (*bookmark && **bookmark)//28. Si no hay '\n', pero bookmark tiene datos
	{
		line = ft_strdup(*bookmark);//29. duplicar lo que hay en bookmark como  a linea
		ft_free(bookmark);
	}
	else
		ft_free(bookmark);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*bookmark;//1. Punto de libro que guarda lo que queda por procesar
	char		*buffer;//2. buffer para almacenar lo que se lee segun buffer_size
	char		*line;//3. linea extraída tras procesar

	line = NULL;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, buffer, 0) < 0 || !buffer)
	{
		ft_free(&bookmark);
		return (ft_free(&buffer));//4. si hay errores se vacian memorias y se devuelve NULL
	}
	line = ft_read_nd_save(&bookmark, fd, buffer, line);//5. la que procesa y pasa linea extraida
	ft_free(&buffer);
	return (line);
}
