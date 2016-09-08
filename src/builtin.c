/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/08 22:54:05 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/08 22:54:29 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		process_builtin(t_env *e)
{
	if (ft_strequ(e->cmd[e->cid].arg[0], "cd"))
		builtin_cd(e);
	else if (ft_strequ(e->cmd[e->cid].arg[0], "echo"))
		builtin_echo(e);
	else if (ft_strequ(e->cmd[e->cid].arg[0], "exit"))
		builtin_exit(e);
	else if (ft_strequ(e->cmd[e->cid].arg[0], "setenv"))
		builtin_setenv(e);
	else if (ft_strequ(e->cmd[e->cid].arg[0], "unsetenv"))
		builtin_unsetenv(e);
	else if (ft_strequ(e->cmd[e->cid].arg[0], "env"))
		builtin_env(e);
	else if (ft_strequ(e->cmd[e->cid].arg[0], "fg"))
		jobs_continue(e, 1);
	else if (ft_strequ(e->cmd[e->cid].arg[0], "bg"))
		jobs_continue(e, 0);
	else if (ft_strequ(e->cmd[e->cid].arg[0], "jobs"))
		jobs_list(e);
	else if (ft_strequ(e->cmd[e->cid].arg[0], "history"))
		history_print(e);
	else if (!process_builtin_2(e))
		return (0);
	return (1);
}

int		process_builtin_2(t_env *e)
{
	if (ft_strequ(e->cmd[e->cid].arg[0], "hash"))
		builtin_hash(e);
	else if (ft_strequ(e->cmd[e->cid].arg[0], "alias"))
		builtin_alias(e);
	else if (ft_strequ(e->cmd[e->cid].arg[0], "unalias"))
		builtin_unalias(e);
	else
		return (0);
	return (1);
}
