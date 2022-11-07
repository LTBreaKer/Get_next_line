/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:23:51 by aharrass          #+#    #+#             */
/*   Updated: 2022/11/07 19:51:56 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(int fd, char *hold)
{
	char		*buf;
	int			rd;

	rd = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (!ft_strchr(hold, '\n') && rd)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
		{
			free (buf);
			free (hold);
			return (NULL);
		}
		buf[rd] = 0;
		hold = ft_strjoin(hold, buf);
		if (!hold)
			return (NULL);
	}
	free (buf);
	return (hold);
}

char	*ft_get_line(char *hold)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!ft_strlen(hold))
		return (NULL);
	while (hold[i] && hold[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	while (j <= i && hold[j])
	{
		line[j] = hold[j];
		j++;
	}
	line[j] = 0;
	return (line);
}

char	*ft_clean(char *hold)
{
	char	*n_hold;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (hold[i] && hold[i] != '\n')
		i++;
	if (!hold[i])
	{
		free (hold);
		return (NULL);
	}
	i++;
	n_hold = malloc(sizeof (char) * (ft_strlen(hold) - i + 1));
	if (!n_hold)
	{
		free (hold);
		return (NULL);
	}
	while (hold[i])
		n_hold[j++] = hold[i++];
	n_hold[j] = 0;
	free (hold);
	return (n_hold);
}

char	*get_next_line(int fd)
{
	static char	*hold[OPEN_MAX];
	char		*line;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	hold[fd] = ft_read(fd, hold[fd]);
	if (!hold[fd])
		return (NULL);
	line = ft_get_line(hold[fd]);
	hold[fd] = ft_clean(hold[fd]);
	return (line);
}
