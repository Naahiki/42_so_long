/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrodrigu <nrodrigu@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:56:16 by nrodrigu          #+#    #+#             */
/*   Updated: 2022/12/04 10:46:59 by nrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (str [i] != '\0')
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return (&str[i]);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	y1;
	unsigned int	y2;
	unsigned int	i;
	unsigned int	x;
	char			*str1;

	if (!s1 || !s2)
		return (NULL);
	y1 = ft_strlen(s1);
	y2 = ft_strlen(s2);
	i = 0;
	x = -1;
	str1 = malloc (sizeof(char) * (y1 + y2 + 1));
	if (!str1)
		return (NULL);
	while (s1[i])
	{
		str1[i] = s1[i];
		i++;
	}
	while (s2[++x])
		str1[i++] = s2[x];
		str1[i] = '\0';
	return (str1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*s_new;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	if (len > ft_strlen (s))
		len = ft_strlen(s);
	i = 0;
	s_new = (char *)malloc(sizeof(char) * (len + 1));
	if (!s_new)
		return (NULL);
	while (start > ft_strlen(s))
	{
		*s_new = '\0';
		return (s_new);
	}
	while (len > 0)
	{
		s_new[i] = s[start];
		i++;
		start++;
		len--;
	}
	s_new[i] = '\0';
	return (s_new);
}