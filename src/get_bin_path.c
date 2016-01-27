/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/27 00:49:25 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	set_bin_path(t_env *e)
{
	char	*path;
	int		i;

	if (e->path)
	{
		i = -1;
		while (e->path[++i])
			free(e->path[i]);
		free(e->path);
	}
	path = get_env_val(e, "PATH");
	if (path)
	{
		e->path = ft_strsplit(path, ':');
		free(path);
	}
	else
		e->path = NULL;
}

char	*get_cmd_path(t_env *e, char *cmd)
{
	char	*cmd_path;

	if (!e->path)
		return (NULL);
	if ((cmd_path = hash_find(e, cmd)))
		return (ft_strdup(cmd_path));
	else if ((cmd_path = hash_add_cmd(e, cmd)))
		return (ft_strdup(cmd_path));
	return (NULL);
}
