/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_sub_and_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/08 22:51:07 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/08 22:51:59 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	process_fork_subcmd(t_env *e, char dofork)
{
	pid_t	pid;

	pid = 0;
	if (!e->sub && !e->background_cmd)
		term_restore_back(e);
	if (dofork)
		pid = fork();
	if (pid > 0 || dofork == 0)
		process_set_child_attr(e, pid);
	if (pid == 0)
	{
		process_init_child(e);
		redirec_assign(e);
		free(e->line);
		e->line = ft_strdup(e->cmd[e->cid].arg[0]);
		free_cmd(e);
		parse_cmd(e);
		exit(e->status);
	}
}

void	process_piped_cmd(t_env *e)
{
	pid_t	pid;

	pid = 0;
	if (!e->sub && !e->background_cmd)
		term_restore_back(e);
	pid = fork();
	if (pid > 0)
		process_set_child_attr(e, pid);
	if (pid == 0)
		process_piped_cmd_child(e);
	else
	{
		process_wait(e, e->cmd[e->cid].pid, 0);
		e->carg = NULL;
	}
}

void	process_piped_cmd_child(t_env *e)
{
	char	dofork;

	process_init_child(e);
	dofork = 1;
	while (e->nb_cmd > e->cid)
	{
		e->carg = e->cmd[e->cid].arg;
		if (!redirec_open_all(e))
			e->cmd[e->cid].status = -1;
		e->cid++;
	}
	e->cid = 0;
	while (e->nb_cmd > e->cid)
	{
		if (e->nb_cmd - 1 == e->cid)
			dofork = 0;
		e->carg = e->cmd[e->cid].arg;
		if (!process_builtin(e))
			process_bin(e, e->var, dofork);
		e->cid++;
	}
	exit(e->status);
}
