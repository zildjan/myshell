/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/10 18:58:17 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/10 02:23:46 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	process_cmd(t_env *e)
{
	int		condi;

	e->step = EXECUTION;
	e->cid = 0;
	e->carg = e->cmd[e->cid].arg;
	if (e->nb_cmd > 1)
		return (process_piped_cmd(e));
	condi = e->cmd[e->cid].condi;
	if (redirec_open_all(e)
		&& ((condi != SEP_AND && condi != SEP_OR)
			|| (condi == SEP_AND && !e->status)
			|| (condi == SEP_OR && e->status)))
	{
		if (!process_builtin(e))
			process_bin(e, e->var, 1);
	}
	if (e->cmd[e->cid].status > 0)
		process_wait(e, e->cmd[e->cid].pid, 0);
	redirec_close(e, e->cid);
	e->carg = NULL;
}

void	process_bin(t_env *e, char **env, char dofork)
{
	char	*cmd_path;
	char	*cmd;

	if (e->cmd[e->cid].sub)
		return (process_fork_subcmd(e, dofork));
	cmd = e->cmd[e->cid].arg[0];
	cmd_path = get_cmd_path(e, cmd);
	if (ft_strchr(cmd, '/') && ft_get_file_type(cmd) != -1)
		cmd_path = ft_strdup(cmd);
	if (cmd_path != NULL)
	{
		process_fork(e, cmd_path, env, dofork);
		free(cmd_path);
	}
	else
	{
		e->status = 127;
		if (ft_strchr(cmd, '/'))
			put_error(ERRNOENT, NULL, cmd, e->cmd[e->cid].fd_err);
		else
			put_error(ERRNOCMD, NULL, cmd, e->cmd[e->cid].fd_err);
	}
}

void	process_fork(t_env *e, char *cmd_path, char **env, char dofork)
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
		if (execve(cmd_path, e->cmd[e->cid].arg, env) == -1)
		{
			if (access(cmd_path, X_OK))
				put_error(ERRACCES, NULL, e->carg[0], e->cmd[e->cid].fd_err);
			else if (ft_get_file_type(cmd_path) == 'd')
				put_error(ERRISDIR, NULL, e->carg[0], e->cmd[e->cid].fd_err);
			else
				put_error(ERREXEFORM, NULL, e->carg[0], e->cmd[e->cid].fd_err);
			exit(126);
		}
	}
}

void	process_set_child_attr(t_env *e, pid_t pid)
{
	if (!e->sub)
	{
		setpgid(pid, pid);
		if (!e->background_cmd)
			term_set_tcpgid(e, pid);
	}
	e->cmd[e->cid].pid = pid;
	e->cmd[e->cid].status = 1;
}

void	process_init_child(t_env *e)
{
	if (!e->sub)
	{
		setpgid(0, getpid());
		if (!e->background_cmd)
			term_set_tcpgid(e, getpid());
	}
	signal_default();
	e->sub = 1;
	if (e->cmd[e->cid].status == -1)
		exit(1);
}
