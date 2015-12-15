/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 20:46:59 by pbourrie         ###   ########.fr       */
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
	if (e->home_dir)
		free(e->home_dir);
	e->home_dir = ft_get_dirup(e->home);
}
