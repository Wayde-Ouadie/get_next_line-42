/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:31:16 by oel-feng          #+#    #+#             */
/*   Updated: 2023/11/26 17:02:05 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_get_line(char **line)
{
	char	*tmp;
	char	*res;
	int		i;

	i = 0;
	while ((*line)[i] && (*line)[i] != '\n') 
		i++;
	if ((*line)[i] == '\n')
	{
		res = ft_substr(*line, 0, i + 1);
		tmp = ft_strdup(*line + i + 1);
		free(*line);
		*line = tmp;
	}
	else
	{
		res = ft_strdup(*line);
		free(*line);
		*line = NULL;
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buffer;
	char		*tmp;
	int			lread;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	lread = 1;
	while (!ft_strchr(line, '\n') && lread != 0)
	{
		lread = read(fd, buffer, BUFFER_SIZE);
		if (lread == -1)
			return (NULL);
		buffer[lread] = '\0';
		tmp = ft_strjoin(line, buffer);
		free(line);
		line = tmp;
	}
	free(buffer);
	return (ft_get_line(&line));
}
