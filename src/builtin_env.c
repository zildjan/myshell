/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/12 19:40:34 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/12 22:46:35 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	builtin_env(t_env *e)
{
	int		opt_i;

	opt_i = 0;
	if (!e->cmd[1])
	{
		ft_putchartab(e->var);
		return ;
	}
	else if (e->cmd[1][0] == '-')
	{
		if (e->cmd[1][1] == 'i')
			opt_i = 1;
		else if (e->cmd[1][1] != '-')
		{
			ft_putstr_fd("env: illegal option -- ", 2);
			ft_putchar_fd(e->cmd[1][1], 2);
			ft_putstr_fd("\nusage: env [-i] [name=value ...] ", 2);
			ft_putendl_fd("[utility [argument ...]]", 2);
			return ;
		}
	}
	builtin_env_setenvtab(e, opt_i);
}

void	builtin_env_setenvtab(t_env *e, int opt_i)
{
	int		i;
	int		id;
	char	**env;

	env = builtin_env_malloctab(e, opt_i);
	id = builtin_env_filltab(e, env, opt_i);
	i = 1;
	if (opt_i)
		i = 2;
	while (e->cmd[i] && ft_strchr(e->cmd[i], '='))
	{
		if (!ft_strcheck(e->cmd[i], ft_isascii))
		{
			ft_putendl_fd("env: Non ascii character.", 2);
			return ;
		}
		env[id++] = ft_strdup(e->cmd[i++]);
	}
	env[id] = NULL;
//	ft_putchartab(env);
	builtin_env_exec(e, env, i);
}

void	builtin_env_exec(t_env *e, char **env, int i)
{
	char	**cmd;
	int		nb_args;
	int		i2;

	nb_args = 0;
	i2 = i;
	while (e->cmd[i2++])
		nb_args++;
	if (!e->cmd[i])
		ft_putchartab(env);
	else
	{
		cmd = (char**)ft_memalloc(sizeof(char*) * (nb_args + 1));
		i2 = 0;
		while (e->cmd[i])
			cmd[i2++] = ft_strdup(e->cmd[i++]);
		cmd[i2] = NULL;
		i2 = 0;
		while (e->cmd[i2])
			free(e->cmd[i2++]);
		free(e->cmd);
		e->cmd = cmd;
		process_cmd(e, env);
		i2 = 0;
		while (env[i2])
			free(env[i2++]);
		free(env);
	}
}

char	**builtin_env_malloctab(t_env *e, int opt_i)
{
	int		size;
	int		i;
	char	**tab;

	size = 0;
	while (!opt_i && e->var[size])
		size++;
	i = 1;
	while (e->cmd[i])
		i++;
	size += i;
	tab = (char**)ft_memalloc(sizeof(char*) * size);
	return (tab);
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
	return (i);
}
