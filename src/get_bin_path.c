/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/07 23:35:13 by pbourrie         ###   ########.fr       */
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
	load_builtin_list(e);
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

void	load_builtin_list(t_env *e)
{
	e->builtin_list = (char **)ft_memalloc(sizeof(char*) * 20);
	e->builtin_list[0] = ft_strdup("cd");
	e->builtin_list[1] = ft_strdup("exit");
	e->builtin_list[2] = ft_strdup("setenv");
	e->builtin_list[3] = ft_strdup("unsetenv");
	e->builtin_list[4] = ft_strdup("env");
	e->builtin_list[5] = ft_strdup("fg");
	e->builtin_list[6] = ft_strdup("jobs");
	e->builtin_list[7] = ft_strdup("history");
	e->builtin_list[8] = ft_strdup("hash");
	e->builtin_list[9] = ft_strdup("echo");
}
