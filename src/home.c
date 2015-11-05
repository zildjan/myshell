/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/10/09 21:27:14 by pbourrie         ###   ########.fr       */
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
		e->home = NULL;
}

char	*parse_home_tilde(t_env *e, char *path)
{
	char	new[MAXPATHLEN + 1];

	ft_bzero(new, MAXPATHLEN + 1);
	if (path[1] == '/')
	{
		ft_strcpy(new, e->home);
		path++;
		ft_strcat(new, path);
	}
	else if (!path[2])
		ft_strcpy(new, e->home);
	else
	{
		path++;
		ft_strcpy(new, "/Users/");
		ft_strcat(new, path);
	}
	return (ft_strdup(new));
}
