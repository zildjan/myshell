/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/01 22:14:24 by pbourrie         ###   ########.fr       */
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
	if (e->hash_total)
		free_hash_table(e);
	e->hash_total = 3;
	e->hash_t = (t_hash_b**)ft_memalloc(sizeof(t_hash_b*) * e->hash_total);
	hash_autofill(e);
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
