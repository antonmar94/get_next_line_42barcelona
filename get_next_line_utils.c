/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonio- <antonio-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:20:34 by antonio-          #+#    #+#             */
/*   Updated: 2024/08/03 17:05:46 by antonio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	size_t	k;
	char	*scopy;

	i = 0;
	j = 0;
	k = 0;
	if (!s1 || !s2)
		return (NULL);
	scopy = (void *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!scopy)
		return (NULL);
	while (i < ft_strlen(s1))
		scopy[i++] = s1[j++];
	while (i < (ft_strlen(s1) + ft_strlen(s2)))
		scopy[i++] = s2[k++];
	scopy[i] = '\0';
	return (scopy);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*copy;

	i = 0;
	while (s1[i] != '\0')
		i++;
	copy = malloc(sizeof(char) * (i + 1));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
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
	res = malloc(sizeof(char) * (len + 1));
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
	res[len] = '\0';
	return (res);
}
