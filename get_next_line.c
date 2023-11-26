/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:31:16 by oel-feng          #+#    #+#             */
/*   Updated: 2023/11/26 21:16:42 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*ft_get_line(char *line)
{
	char	*tmp;
	char	*res;
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n') 
		i++;
	if (!line)
		return (NULL);
	res = ft_substr(line, 0, i + 1);
	if (!res)
	{
		if (line)
			return (line);
		line = NULL;
		return (NULL);
	}
	if (res == NULL)
	{
		free(res);
		res = NULL;
	}
	line[i + 1] = '\0';
	return (res);
}

static char	*read_line_check(int fd, char *buff, char *line)
{
	int	lread;

	lread = 1;
	while (lread > 0)
	{
		lread = read(fd, buff, BUFFER_SIZE);
		if (lread == -1)
			return (NULL);
		else if (lread == 0)
			break ;
		buff[lread] = '\0';
		if (!line)
			line = ft_strdup("");
		line = ft_strjoin(line, buff);
		free(line);
		if (!line)
			return (NULL);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	line = read_line_check(fd, buff, line);
	free(buff);
	buff = NULL;
	if (!line)
		return (free(line), NULL);
	line = ft_get_line(line);
	return (line);
}
