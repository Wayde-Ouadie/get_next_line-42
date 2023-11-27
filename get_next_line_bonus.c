/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:31:16 by oel-feng          #+#    #+#             */
/*   Updated: 2023/11/27 12:52:48 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <sys/syslimits.h>

static char	*ft_get_line(char *line)
{
	char	*res;
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n') 
		i++;
	if (line[i] == '\0')
		return (NULL);
	res = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!res)
	{
		if (line)
			free(line);
		line = NULL;
		return (NULL);
	}
	if (*res == '\0')
	{
		free(res);
		res = NULL;
	}
	line[i + 1] = '\0';
	return (res);
}

static char	*read_line_check(int fd, char *buff, char *line)
{
	int		lread;
	char	*tmp;

	lread = 1;
	while (lread)
	{
		lread = read(fd, buff, BUFFER_SIZE);
		if (lread == -1)
			return (NULL);
		else if (lread == 0)
			break ;
		buff[lread] = '\0';
		if (!line)
			line = ft_strdup("");
		tmp = line;
		line = ft_strjoin(tmp, buff);
		free(tmp);
		tmp = NULL;
		if (!line)
			return (NULL);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
  static char *line[10240];
  char *tmp;
  char *buff;

  if (fd < 0 || BUFFER_SIZE <= 0 || fd > 10240)
    return (NULL);
  buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
  if (!buff)
    return (NULL);
  tmp = read_line_check(fd, buff, line[fd]);
  free(buff);
  buff = NULL;
  if (!tmp) {
    if (line[fd])
      free(line[fd]);
    line[fd] = NULL;
    return (NULL);
	}
	line[fd] = ft_get_line(tmp);
	return (tmp);
}