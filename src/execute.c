/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/10 18:58:17 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/04 00:44:58 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	process_cmd(t_env *e)
{
	int		condi;

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

void	process_set_child_attr(t_env *e, int pid)
{
	if (!e->sub)
	{
		setpgid(pid, pid);
		if (!e->background_cmd)
			tcsetpgrp(0, pid);
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
			tcsetpgrp(0, getpid());
	}
	signal_default();
	e->sub = 1;
	if (e->cmd[e->cid].status == -1)
		exit(1);
}

void	process_piped_cmd(t_env *e)
{
	int		pid;

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
	int		pid;

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

//		ft_printf("EXEC '%s'\n", cmd_path);
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

void	process_fork_subcmd(t_env *e, char dofork)
{
//	ft_printf("subcmd='%s'\n", e->cmd[e->cid].arg[0]);

	int		pid;

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
// */
}

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
