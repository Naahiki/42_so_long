/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrodrigu <nrodrigu@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:55:55 by nrodrigu          #+#    #+#             */
/*   Updated: 2022/12/04 10:44:15 by nrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_lines(int fd, char *buf, char *stash)
{
	int		read_line;
	char	*aux;

	read_line = 1;
	while (read_line > 0)
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line < 0)
			return (0);
		else if (read_line == 0)
			break ;
		if (!stash)
		{
			stash = (char *)malloc(sizeof(char) * 1);
			stash[0] = '\0';
		}
		buf[read_line] = '\0';
		aux = stash;
		stash = ft_strjoin(aux, buf);
		free(aux);
		aux = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (stash);
}

char	*get_lines(char *line)
{
	int		i;
	char	*stash;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (0);
	stash = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*stash == '\0')
	{
		free(stash);
		stash = NULL;
	}
	line[i + 1] = '\0';
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	line = read_lines(fd, buf, stash);
	free(buf);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (0);
	}
	stash = get_lines(line);
	return (line);
}