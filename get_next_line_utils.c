/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonio- <antonio-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:20:34 by antonio-          #+#    #+#             */
/*   Updated: 2024/09/06 21:20:38 by antonio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;
	size_t	i;
	size_t	malloc_size;

	i = 0;
	malloc_size = nmemb * size;
	buffer = malloc(malloc_size);
	if (!buffer)
		return (buffer);
	while (i < malloc_size)
	{
		((char *)buffer)[i] = 0;
		i++;
	}
	return (buffer);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	sum_len;
	char	*scopy;

	i = 0;
	j = 0;
	s1_len = ft_strlen(s1);
	sum_len = s1_len + ft_strlen(s2);
	scopy = ft_calloc(sizeof(char), (sum_len + 1));
	if (!scopy)
		return (NULL);
	while (i < s1_len)
		scopy[i++] = s1[j++];
	j = 0;
	while (i < sum_len)
		scopy[i++] = s2[j++];
	return (scopy);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*copy;

	i = 0;
	while (s1[i] != '\0')
		i++;
	copy = ft_calloc(sizeof(char), (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	return (copy);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	s_len;

	i = 0;
	if (start > ft_strlen(s))
		s_len = 0;
	else
		s_len = ft_strlen(s) - start;
	if (s_len < len)
		len = s_len;
	res = ft_calloc(sizeof(char), (len + 1));
	if (!res)
		return (res);
	if (start >= ft_strlen((char *) s))
		return (res);
	s += start;
	while (i < len && s[i])
	{
		res[i] = s[i];
		i++;
	}
	return (res);
}
