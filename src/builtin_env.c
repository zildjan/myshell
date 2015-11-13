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

	opt_i = 0;
	if (!e->cmd[1])
	{
		ft_putchartab(e->var);
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
	while (e->cmd[++*i] && e->cmd[*i][0] == '-' && i2 >= 0)
	{
		i2 = 0;
		while (e->cmd[*i][++i2])
		{
			if (e->cmd[*i][i2] == 'i')
				*opt_i = 1;
			else if (e->cmd[*i][i2] == '-')
				return (++*i);
			else if (e->cmd[*i][i2] && e->cmd[*i][i2] != 'i')
			{
				ft_putstr_fd("env: illegal option -- ", 2);
				ft_putchar_fd(e->cmd[*i][i2], 2);
				ft_putstr_fd("\nusage: env [-i] [name=value ...] ", 2);
				ft_putendl_fd("[utility [argument ...]]", 2);
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

	env = builtin_env_malloctab(e, opt_i);
	id = builtin_env_filltab(e, env, opt_i);
	while (e->cmd[i] && ft_strchr(e->cmd[i], '='))
	{
		if (!ft_strcheck(e->cmd[i], ft_isascii))
		{
			ft_putendl_fd("env: Non ascii character.", 2);
			return ;
		}
		builtin_env_insertnewent(e, env, &id, i++);
	}
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
	while (e->cmd[i][len] != '=' && e->cmd[i][len])
		len++;
	i2 = -1;
	while (env[++i2])
		if (ft_strnequ(e->cmd[i], env[i2], len) && e->cmd[i][len] == '=')
			break ;
	if (i2 >= 0)
	{
		free(env[i2]);
		env[i2] = ft_strdup(e->cmd[i]);
	}
	else
	{
		env[*id++] = ft_strdup(e->cmd[i]);
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
	}
}
