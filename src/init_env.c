/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/07 01:25:09 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_env	*init_env(int argc, char **argv, char **environ)
{
	t_env	*e;

	e = (t_env*)ft_memalloc(sizeof(t_env));
	if (argc && argv)
		init_env_var(e, environ);
	e->job = NULL;
	e->jobs_lst = NULL;
	e->path = NULL;
	set_bin_path(e);
	e->home = NULL;
	set_home_path(e);
	init_pwd(e);
	e->status = 0;
	e->clipboard = NULL;
	refresh_nb_col(e);
	init_shlvl(e);
	term_init(e);
	history_init(e);
	return (e);
}

void	init_env_var(t_env *e, char **environ)
{
	int		i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	e->tab_size = i + 10;
	e->var = (char**)ft_memalloc(sizeof(char*) * e->tab_size);
	i = 0;
	while (environ[i] != NULL)
	{
		e->var[i] = ft_strdup(environ[i]);
		i++;
	}
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

void	init_pwd(t_env *e)
{
	e->pwd = get_env_val(e, "PWD");
	if (ft_get_file_type(e->pwd) != 'd')
	{
		if (e->pwd)
			free(e->pwd);
		e->pwd = getcwd(NULL, 0);
	}
	if (!e->pwd)
		e->pwd = ft_strdup("/");
}

void	refresh_nb_col(t_env *e)
{
	struct winsize win;

	completion_free(e);
	if (ioctl(1, TIOCGWINSZ, &win) == 0)
		e->ws_col = win.ws_col;
	else
		e->ws_col = 80;
}
