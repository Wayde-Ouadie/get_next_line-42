/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:31:16 by oel-feng          #+#    #+#             */
/*   Updated: 2023/12/31 03:23:00 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_data(int fd, char *buffer, char *data)
{
	ssize_t	lread;

	lread = 1;
	while (lread && !ft_strchr(buffer, '\n'))
	{
		lread = read(fd, buffer, BUFFER_SIZE);
		if (lread < 0)
			return (free(data), data = NULL, NULL);
		buffer[lread] = 0;
		data = ft_strjoin(data, buffer);
	}
	return (data);
}

static char	*gettingline(char *data)
{
	int	i;

	i = 0;
	while (data[i] && data[i] != '\n')
		i++;
	return (ft_substr(data, 0, i + 1));
}

static char	*updata(char *data)
{
	char	*tmp;
	int		i;

	i = 0;
	while (data[i] && data[i] != '\n')
		i++;
	(data[i] == '\n') && (i += 1);
	tmp = ft_substr(data, i, ft_strlen(data + i));
	return (free(data), tmp);
}

char	*get_next_line(int fd)
{
	static char	*data[OPEN_MAX];
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX || fd >= OPEN_MAX)
		return (NULL);
	buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (free(data[fd]), NULL);
	buffer[0] = 0;
	data[fd] = read_data(fd, buffer, data[fd]);
	free(buffer);
	if (!data[fd])
		return (NULL);
	if (!*data[fd])
		return (free(data[fd]), data[fd] = NULL, NULL);
	return (line = gettingline(data[fd]), data[fd] = updata(data[fd]), line);
}
