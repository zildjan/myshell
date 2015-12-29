/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/12 19:36:00 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	builtin_setenv(t_env *e)
{
	e->status = 1;
	if (!e->carg[1])
		ft_putchartab_fd(e->var, e->cmd[e->cid].fd_out);
	else if (e->carg[2] && e->carg[3])
		ft_putendl_fd("setenv: Too many arguments.", e->cmd[e->cid].fd_err);
	else if (builtin_setenv_check(e->carg[1], 0))
		ft_putendl_fd("setenv: Non alnum character.", e->cmd[e->cid].fd_err);
	else if (builtin_setenv_check(e->carg[2], 0))
		ft_putendl_fd("setenv: Non alnum character.", e->cmd[e->cid].fd_err);
	else if (e->carg[1] && ft_strchr(e->carg[1], '='))
		ft_putendl_fd("setenv: Syntax error : '='.", e->cmd[e->cid].fd_err);
	else if (e->carg[2] && ft_strchr(e->carg[2], '='))
		ft_putendl_fd("setenv: Syntax error : '='.", e->cmd[e->cid].fd_err);
	else
	{
		e->status = 0;
		set_env_var(e, e->carg[1], e->carg[2]);
	}
}

int		builtin_setenv_check(char *str, int egual)
{
	size_t	i;

	if (!str)
		return (0);
	while (egual && str[0] == '=')
		return (1);
	i = 0;
	while (ft_isprint(str[i]))
		i++;
	if (ft_strlen(str) == i)
		return (0);
	else
		return (1);
}

void	builtin_unsetenv(t_env *e)
{
	int		i;

	e->status = 0;
	if (!e->carg[1])
	{
		e->status = 1;
		ft_putendl_fd("unsetenv: Too few arguments.", e->cmd[e->cid].fd_err);
	}
	else
	{
		i = 0;
		while (e->carg[i])
		{
			unset_env_var(e, e->carg[i]);
			i++;
		}
	}
}
