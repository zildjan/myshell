/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/10/09 21:27:14 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

extern char **environ;

t_env	*init_env(void)
{
	t_env	*e;

	e = (t_env*)ft_memalloc(sizeof(t_env));
	e->val = (char**)ft_memalloc(sizeof(char*) * 1000);

	int i;

	i = 0;
	while (environ[i] != NULL)
	{
		e->val[i] = ft_strdup(environ[i]);
		i++;
	}

	set_bin_path(e);

	return (e);
}
