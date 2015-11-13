/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 18:17:52 by pbourrie         ###   ########.fr       */
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
	int		i;
	char	cmd_path[MAXPATHLEN + 1];
	char	type;

	if (!e->path)
		return (NULL);
	i = 0;
	while (e->path[i])
	{
		ft_bzero(cmd_path, MAXPATHLEN + 1);
		ft_strcpy(cmd_path, e->path[i]);
		ft_strcat(cmd_path, "/");
		ft_strcat(cmd_path, cmd);
		type = ft_get_file_type(cmd_path);
		if (type == '-' || type == 'l')
			return (ft_strdup(cmd_path));
		i++;
	}
	return (NULL);
}
