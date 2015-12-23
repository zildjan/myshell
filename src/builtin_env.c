/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/12 19:40:34 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 19:04:36 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	builtin_env(t_env *e)
{
	int		opt_i;
	int		i;

	e->status = 0;
	opt_i = 0;
	if (!e->carg[1])
	{
		ft_putchartab_fd(e->var, e->cmd[e->cid].fd_out);
		return ;
	}
	i = 0;
	if (!builtin_env_getopt(e, &i, &opt_i))
		return ;
	builtin_env_setenvtab(e, opt_i, i);
}

int		builtin_env_getopt(t_env *e, int *i, int *opt_i)
{
	int	i2;

	i2 = 0;
	while (e->carg[++*i] && e->carg[*i][0] == '-' && i2 >= 0)
	{
		i2 = 0;
		while (e->carg[*i][++i2])
		{
			if (e->carg[*i][i2] == 'i')
				*opt_i = 1;
			else if (e->carg[*i][i2] == '-')
				return (++*i);
			else if (e->carg[*i][i2] && e->carg[*i][i2] != 'i')
			{
				ft_putstr_fd("env: illegal option -- ", e->cmd[e->cid].fd_err);
				ft_putchar_fd(e->carg[*i][i2], e->cmd[e->cid].fd_err);
				ft_putstr_fd("\nusage: env [-i] [name=value ...] ", e->cmd[e->cid].fd_err);
				ft_putendl_fd("[utility [argument ...]]", e->cmd[e->cid].fd_err);
				e->status = 1;
				return (0);
			}
		}
	}
	return (1);
}

void	builtin_env_setenvtab(t_env *e, int opt_i, int i)
{
	int		id;
	char	**env;
	int		error;

	error = 0;
	env = builtin_env_malloctab(e, opt_i);
	id = builtin_env_filltab(e, env, opt_i);
	while (e->carg[i] && ft_strchr(e->carg[i], '='))
	{
		if (builtin_setenv_check(e->carg[i], 1))
		{
			ft_putendl_fd("env: Non alnum character.", e->cmd[e->cid].fd_err);
			error = 1;
			e->status = 1;
			break ;
		}
		if (!error)
			builtin_env_insertnewent(e, env, &id, i++);
	}
	if (!error)
		builtin_env_exec(e, env, i);
	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

void	builtin_env_insertnewent(t_env *e, char **env, int *id, int i)
{
	int		len;
	int		i2;

	len = 0;
	while (e->carg[i][len] != '=' && e->carg[i][len])
		len++;
	i2 = -1;
	while (env[++i2])
		if (ft_strnequ(e->carg[i], env[i2], len) && e->carg[i][len] == '=')
			break ;
	if (i2 >= 0)
	{
		free(env[i2]);
		env[i2] = ft_strdup(e->carg[i]);
	}
	else
	{
		env[*id++] = ft_strdup(e->carg[i]);
		env[*id] = NULL;
	}
}

void	builtin_env_exec(t_env *e, char **env, int i)
{
	char	**cmd;
	int		nb_args;
	int		i2;

	nb_args = 0;
	i2 = i;
	while (e->carg[i2++])
		nb_args++;
	if (!e->carg[i])
		ft_putchartab_fd(env, e->cmd[e->cid].fd_out);
	else
	{
		cmd = (char**)ft_memalloc(sizeof(char*) * (nb_args + 1));
		i2 = 0;
		while (e->carg[i])
			cmd[i2++] = ft_strdup(e->carg[i++]);
		cmd[i2] = NULL;
		i2 = 0;
		while (e->carg[i2])
			free(e->carg[i2++]);
		free(e->carg);
		e->carg = cmd;
		e->cmd[e->cid].arg = e->carg;
		process_bin(e, env);
	}
}
