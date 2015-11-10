/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/10 18:50:36 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	set_home_path(t_env *e)
{
	char	*path;

	if (e->home)
		free(e->home);
	path = get_env_val(e, "HOME");
	if (path)
		e->home = path;
	else
		e->home = ft_strdup("");
	e->home_dir = ft_get_dirup(e->home);
}

void	parse_home_tilde(t_env *e, int i)
{
	char	new[MAXPATHLEN + 1];
	char	*path;

	path = e->cmd[i];
	if (path[0] != '~')
		return ;
	ft_bzero(new, MAXPATHLEN + 1);
	if (path[1] == '/')
	{
		ft_strcpy(new, e->home);
		path++;
		ft_strcat(new, path);
	}
	else if (!path[1])
		ft_strcpy(new, e->home);
	else
	{
		path++;
		ft_strcpy(new, e->home_dir);
		ft_strcat(new, path);
	}
	free(e->cmd[i]);
	e->cmd[i] = ft_strdup(new);
}
