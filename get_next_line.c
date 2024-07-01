/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonio- <antonio-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:55:30 by antonio-          #+#    #+#             */
/*   Updated: 2024/07/01 21:12:31 by antonio-         ###   ########.fr       */
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
	*line = ft_substr(*file, 0, newline_pos(*file));
	*file = ft_substr(*file, newline_pos(*file) + 1, ft_strlen(*file));
	free_file(&temp);
}

char	*get_next_line(int fd)
{
	static char	*file[4096];
	char		*buffer;
	char		*line;
	int			buffer_tam;

	
	printf("EMPEZAMOS\n");
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	buffer_tam = 1;
	printf("BUFFER %s\n", file[fd]);
	while (!(ft_strchr(file[fd], '\n')) && buffer_tam != 0)
	{
		buffer_tam = read(fd, buffer, BUFFER_SIZE);
		if (buffer_tam == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[buffer_tam] = '\0';
		printf("BUFFER %s\n", buffer);
		file_filler(&file[fd], buffer);
	}
	free(buffer);
	line_filler(&line, &file[fd]);
	printf("LINE %s\n", line);
	if (buffer_tam == 0)
		return (free_file(&file[fd]));
	return (line);
}

int	main(int argc, char **argv)
{

	int fd = open(argv[1], 1);

	printf("Linea actual %s", get_next_line(fd));

}
