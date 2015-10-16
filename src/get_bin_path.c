/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/10/09 21:25:29 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <sys/mount.h>

void	set_bin_path(t_env *e)
{
	char	*path;

	path = get_env_val(e, "PATH");
	e->path = ft_strsplit(path, ':');
	free(path);
}

char	*get_cmd_path(t_env *e, char *cmd)
{
	int		i;
	char	cmd_path[MAXPATHLEN + 1];

	i = 0;
	while (e->path[i])
	{
		ft_bzero(cmd_path, MAXPATHLEN + 1);
		ft_strcpy(cmd_path, e->path[i]);
		ft_strcat(cmd_path, "/");
		ft_strcat(cmd_path, cmd);
		if (ft_get_file_type(cmd_path) == '-')
			return (ft_strdup(cmd_path));
		i++;
	}
	if (ft_get_file_type(cmd) == '-')
		return (ft_strdup(cmd));
	return (NULL);
}
