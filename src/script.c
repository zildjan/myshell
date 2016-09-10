/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 23:32:56 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/09 23:54:18 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	load_rc(t_env *e)
{
	char	*path;

	path = ft_strdup(e->home);
	path = ft_strdupcat(path, "/.42shrc");
	execute_script(e, path, 0);
	free(path);
	e->fd_in = 0;
}

int		execute_script(t_env *e, char *path, char error)
{
	int		fd;
	int		ret;

	fd = 0;
	if ((ret = execute_script_open(path, &fd, error)) != 0)
		return (ret);
	e->fd_in = fd;
	e->line = NULL;
	while (e->fd_in > 0)
	{
		get_cmd(e);
	}
	if (e->line)
		free(e->line);
	close(fd);
	return (e->status);
}

int		execute_script_open(char *path, int *fd, char error)
{
	int		type;
	int		ret;

	ret = 126;
	type = ft_get_file_type(path);
	if (type == -1)
		ret = 127;
	if (type != 'd')
		*fd = open(path, O_RDONLY);
	if (*fd <= 0)
	{
		if (error)
		{
			if (type == -1)
				put_error(ERRNOENT, NULL, path, 2);
			else if (type == 'd')
				put_error(ERRISDIR, NULL, path, 2);
			else if (access(path, R_OK))
				put_error(ERRACCES, NULL, path, 2);
			else
				put_error(100, NULL, path, 2);
		}
		return (ret);
	}
	return (0);
}
