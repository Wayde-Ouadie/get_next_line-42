/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:31:16 by oel-feng          #+#    #+#             */
/*   Updated: 2023/11/26 19:22:56 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*ft_get_line(char **line)
{
	char	*tmp;
	char	*res;
	int		i;

	i = 0;
	if (!*line)
		return (NULL);
	while ((*line)[i] && (*line)[i] != '\n') 
		i++;
	if ((*line)[i] == '\n')
	{
		res = ft_substr(*line, 0, i + 1);
		tmp = ft_strdup(*line + i + 1);
		if (!tmp)
			return (free(res), NULL);
		free(*line);
		*line = tmp;
	}
	else
	{
		res = ft_strdup(*line);
		if (!res)
			return (NULL);
		free(*line);
		*line = NULL;
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buff;
	char		*tmp;
	int			lread;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	lread = 1;
	while (!ft_strchr(line, '\n') && lread < 0)
	{

		lread = read(fd, buff, BUFFER_SIZE);
		if (lread == -1)
			return (free(buff), NULL);
		buff[lread] = '\0';
		line = ft_strjoin(line, buff);
		free(line);
		line = tmp;
	}
	free(buff);
	return (ft_get_line(&line));
}
