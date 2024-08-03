/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonio- <antonio-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:55:30 by antonio-          #+#    #+#             */
/*   Updated: 2024/08/03 18:05:00 by antonio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static char	*free_file(char **file)
{
	if (*file)
		free(*file);
	*file = NULL;
	return (NULL);
}

static int	newline_pos(char *file)
{
	int	i;

	i = 0;
	while (file[i] != '\n' && file[i] != '\0')
		i++;
	printf("Posicion de la nueva linea %i\n", i);
	return (i);
}

static void	file_filler(char **file, char *buffer)
{
	char		*temp;

	if (*file == NULL)
		*file = ft_strdup(buffer);
	else
	{
		temp = *file;
		*file = ft_strjoin(*file, buffer);
		free_file(&temp);
	}
}

static void	line_filler(char **line, char **file)
{
	char		*temp;

	temp = *file;
	printf("FILE ES %s\n", temp);

	printf("LINE ANTES ES %s\n", *line);
	*line = ft_substr(temp, 0, newline_pos(temp));
	printf("LINE DESPUES ES %s\n", *line);
	*file = ft_substr(temp, newline_pos(*file) + 1, ft_strlen(*file));
	free(temp);
}

char	*get_next_line(int fd)
{
	static char	*file[4096];
	char		*buffer;
	char		*line;
	int			buffer_tam;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	buffer_tam = 1;
	while (!(ft_strchr(file[fd], '\n')) && buffer_tam != 0)
	{
		buffer_tam = read(fd, buffer, BUFFER_SIZE);
		if (buffer_tam == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[buffer_tam] = '\0';
		file_filler(&file[fd], buffer);
	}
	free(buffer);
	line_filler(&line, &file[fd]);
	if (buffer_tam == 0)
		return (free_file(&file[fd]));
	return (line);
}

int	main(int argc, char **argv)
{
	(void)argc;
	int fd = open(argv[1], 2);

	printf("Linea actual %s\n", get_next_line(fd));
	/*printf("Linea actual %s\n", get_next_line(fd));
	printf("Linea actual %s\n", get_next_line(fd));*/
}
