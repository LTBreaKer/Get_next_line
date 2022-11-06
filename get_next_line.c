/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 22:42:25 by aharrass          #+#    #+#             */
/*   Updated: 2022/11/06 11:41:49 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *hold)
{
	char		*buf;
	int			rd;

	rd = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (!is_nl(hold) && rd)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd < 0)
		{
			free (hold);
			free (buf);
			return (NULL);
		}
		buf[rd] = 0;
		hold = ft_strjoin(hold, buf);
		if (!hold)
			return (NULL);
		free (buf);
	}
	return (hold);
}

char	*ft_get_line(char *hold)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (hold[i] && hold[i] != '\n')
		i++;
	if (hold[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
	{
		free (hold);
		return (NULL);
	}
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
	n_hold = malloc(sizeof (char) * (ft_strlen(hold) - i + 1));
	if (!n_hold)
		return (NULL);
	while (hold[i])
		n_hold[j++] = hold[i++];
	n_hold[j] = 0;
	free (hold);
	return (n_hold);
}

char	*get_next_line(int fd)
{
	static char	*hold;
	char		*line;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &hold, 0) < 0)
		return (NULL);
	hold = ft_read(fd, hold);
	if (!hold)
		return (NULL);
	line = ft_get_line(hold);
	hold = ft_clean(hold);
	return (line);
}

int main()
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		printf("\n%s", get_next_line(fd));
		if (!get_next_line(fd))
			break;
	}
	return (0);
}