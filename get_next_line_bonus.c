/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonio- <antonio-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:55:30 by antonio-          #+#    #+#             */
/*   Updated: 2024/09/07 12:55:11 by antonio-         ###   ########.fr       */
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
	static char	*file[FOPEN_MAX];
	char		*buffer;
	char		*line;
	int			buffer_tam;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > FOPEN_MAX)
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
	int fd1;
	int fd2;
	int fd3;
	char *line;

	fd1 = open(argv[1], 2);
	fd2 = open(argv[2], 2);
	fd3 = open(argv[3], 2);

	line = get_next_line(fd3);
	printf("%s", line);
	free(line);
	line = get_next_line(fd1);
	printf("%s", line);
	free(line);
	line = get_next_line(fd1);
	printf("%s", line);
	free(line);
	line = get_next_line(fd2);
	printf("%s", line);
	free(line);
	line = get_next_line(fd3);
	printf("%s", line);
	free(line);
	line = get_next_line(fd2);
	while (line) {
		printf("%s", line);
		free(line);	
		line = get_next_line(fd2);
	}
	close(fd1);
	close(fd2);
	close(fd3);
}*/
