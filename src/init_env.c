/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/09 20:53:24 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

extern char **environ;

t_env	*init_env(void)
{
	t_env	*e;

	e = (t_env*)ft_memalloc(sizeof(t_env));
	e->var = (char**)ft_memalloc(sizeof(char*) * 10000);

	int i;

	i = 0;
	while (environ[i] != NULL)
	{
		e->var[i] = ft_strdup(environ[i]);
		i++;
	}

	e->path = NULL;
	set_bin_path(e);
	e->home = NULL;
	set_home_path(e);
	e->pwd = getcwd(NULL, 0);
	e->status = 0;

	init_shlvl(e);

	return (e);
}

void	init_shlvl(t_env *e)
{
	char	*shlvl;
	char	*new_shlvl;

	shlvl = get_env_val(e, "SHLVL");
	if (shlvl && ft_strcheck(shlvl, ft_isdigit))
		new_shlvl = ft_itoa(ft_atoi(shlvl) + 1);
	else
		new_shlvl = ft_itoa(1);
	set_env_var(e, "SHLVL", new_shlvl);
	free(shlvl);
	free(new_shlvl);
}
