/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonio- <antonio-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:55:30 by antonio-          #+#    #+#             */
/*   Updated: 2024/09/06 21:22:15 by antonio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
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

static int	file_filler(int fd, char **file, char *buffer)
{
	char		*temp;
	int			buffer_tam;

	buffer_tam = read(fd, buffer, BUFFER_SIZE);
	if (buffer_tam == -1)
	{
		free(*file);
		*file = NULL;
		free(buffer);
		return (buffer_tam);
	}
	buffer[buffer_tam] = '\0';
	if (*file == NULL)
		*file = ft_strdup(buffer);
	else
	{
		temp = *file;
		*file = ft_strjoin(temp, buffer);
		free(temp);
	}
	return (buffer_tam);
}

static void	line_filler(char **line, char **file)
{
	char		*temp;
	int			newlinepos;

	temp = *file;
	newlinepos = newline_pos(temp);
	*line = ft_substr(temp, 0, newlinepos + 1);
	*file = ft_substr(temp, newline_pos(*file) + 1, ft_strlen(*file));
	free(temp);
	if (*file && !**file)
	{
		free(*file);
		*file = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*file[4096];
	char		*buffer;
	char		*line;
	int			buffer_tam;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer_tam = 1;
	while (!file[fd] || (!(ft_strchr(file[fd], '\n')) && buffer_tam != 0))
	{
		buffer_tam = file_filler(fd, &file[fd], buffer);
		if (buffer_tam == -1)
			return (NULL);
	}
	free(buffer);
	line_filler(&line, &file[fd]);
	if (buffer_tam == 0 && (!line || !*line))
	{
		free(line);
		line = NULL;
	}
	return (line);
}

/*int	main(int argc, char **argv)
{
	(void)argc;
	int fd = open(argv[1], 2);
	char *line;

	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close(fd);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	fd = open(argv[1], 2);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close(fd);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	fd = open(argv[1], 2);
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	while (line) {
		printf("%s", line);
		free(line);	
		line = get_next_line(fd);
	}
	close(fd);
}*/
