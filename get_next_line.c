/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonio- <antonio-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:55:30 by antonio-          #+#    #+#             */
/*   Updated: 2024/08/07 20:07:27 by antonio-         ###   ########.fr       */
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
		*file = ft_strjoin(temp, buffer);
		free(temp);
	}
}

static void	line_filler(char **line, char **file)
{
	char		*temp;

	temp = *file;
	if (*temp)
		*line = ft_substr(temp, 0, newline_pos(temp) + 1);
	else
		line = NULL;
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
	if (!buffer)
		return (NULL);
	buffer_tam = 1;
	while (!file[fd] || (!(ft_strchr(file[fd], '\n')) && buffer_tam != 0))
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

/*int	main(int argc, char **argv)
{
	(void)argc;
	int fd = open(argv[1], 2);
	char *line;

	line = get_next_line(fd);
	while (line) {
		printf("%s", line);
		free(line);	
		line = get_next_line(fd);
	}
	free(line);
	printf("Linea actual %s\n", get_next_line(fd));
	printf("Linea actual %s\n", get_next_line(fd));
}*/
