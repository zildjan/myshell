/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/13 19:03:38 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 19:04:33 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	**builtin_env_malloctab(t_env *e, int opt_i)
{
	int		size;
	int		i;
	char	**stab;

	size = 0;
	while (!opt_i && e->var[size])
		size++;
	i = 1;
	while (e->carg[i])
		i++;
	size += i;
	stab = (char**)ft_memalloc(sizeof(char*) * size);
	return (stab);
}

int		builtin_env_filltab(t_env *e, char **env, int opt_i)
{
	int		i;

	i = 0;
	while (!opt_i && e->var[i])
	{
		env[i] = ft_strdup(e->var[i]);
		i++;
	}
	env[i] = NULL;
	return (i);
}
