/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 19:13:15 by pbourrie          #+#    #+#             */
/*   Updated: 2015/04/17 23:10:40 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		refresh_line(char **buffer, char **line, int ret)
{
	char	*temp;

	temp = ft_strchr(*buffer, '\n');
	if (temp)
	{
		*line = ft_strsub(*buffer, 0, temp - *buffer);
		temp = ft_strsub(temp, 1, ft_strlen(temp));
		free(*buffer);
		*buffer = temp;
		return (1);
	}
	if (ret == 0)
	{
		*line = ft_strdup(*buffer);
		if (*buffer)
			free(*buffer);
		*buffer = NULL;
		if (*line[0] != 0)
			return (1);
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	char		*temp;
	char		buf[GNL_BUFF_SIZE + 1];
	int			ret;
	static char	*buffer = NULL;

	if (!line || GNL_BUFF_SIZE < 1)
		return (-1);
	if (!buffer)
		buffer = ft_strdup("");
	ret = 1;
	if (!ft_strchr(buffer, '\n'))
		while (1)
		{
			ft_bzero(buf, GNL_BUFF_SIZE + 1);
			if ((ret = read(fd, buf, GNL_BUFF_SIZE)) == -1)
				return (-1);
			temp = ft_strjoin(buffer, buf);
			if (buffer)
				free(buffer);
			buffer = temp;
			if (ft_strchr(buf, '\n') || ret == 0)
				break ;
		}
	return (refresh_line(&buffer, line, ret));
}
