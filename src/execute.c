/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/10 18:58:17 by pbourrie          #+#    #+#             */
/*   Updated: 2016/06/27 02:32:56 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	process_cmd(t_env *e)
{
	int		condi;

	e->cid = 0;
	e->wait_cid = 0;
	while (e->nb_cmd > e->cid)
	{
//		ft_printf("condi=%d\n", e->cmd[e->cid].condi);
		e->carg = e->cmd[e->cid].arg;
		condi = e->cmd[e->cid].condi;
		if (condi != SEP_PIPE)
			e->cmd_pgid = 0;
		if (redirec_open_all(e)
			&& ((condi != SEP_AND && condi != SEP_OR)
				|| (condi == SEP_AND && !e->status)
				|| (condi == SEP_OR && e->status)))
		{
			if (!process_builtin(e))
				process_bin(e, e->var);
			if (e->cmd[e->cid].status)
				redirec_close(e, e->cid);
			process_wait_list(e);
		}
		e->cid++;
	}
	process_wait_list(e);
	e->carg = NULL;
}

void	process_bin(t_env *e, char **env)
{
	char	*cmd_path;
	char	*cmd;

	if (e->cmd[e->cid].sub)
	{
		process_fork_subcmd(e);
		return ;
	}
	cmd = e->cmd[e->cid].arg[0];
	cmd_path = get_cmd_path(e, cmd);
	if (ft_strchr(cmd, '/') && ft_get_file_type(cmd) != -1)
		cmd_path = ft_strdup(cmd);
	if (cmd_path != NULL)
	{
		term_restore_back(e);
		process_fork(e, cmd_path, env);
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

void	process_fork(t_env *e, char *cmd_path, char **env)
{
	int		child;

	child = fork();
	if (child > 0)
	{
		e->cmd[e->cid].pid = child;
		if (e->cmd[e->cid].condi != SEP_PIPE || e->cmd_pgid == 0)
			e->cmd_pgid = child;
		e->cmd[e->cid].status = 1;
	}
	else if (child == 0)
	{
		setpgid(e->cmd[e->cid].pid, e->cmd_pgid);
		tcsetpgrp(0, getpid());
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

void	process_fork_subcmd(t_env *e)
{
//	ft_printf("subcmd='%s'\n", e->cmd[e->cid].arg[0]);

	int		child;

	child = fork();
	if (child > 0)
	{
		e->cmd[e->cid].pid = child;
		if (e->cmd[e->cid].condi != SEP_PIPE || e->cmd_pgid == 0)
			e->cmd_pgid = child;
		e->cmd[e->cid].status = 1;
	}
	else if (child == 0)
	{
		setpgid(e->cmd[e->cid].pid, e->cmd_pgid);
		tcsetpgrp(0, getpid());
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
		jobs_continue(e);
	else if (ft_strequ(e->cmd[e->cid].arg[0], "jobs"))
		jobs_list(e);
	else if (ft_strequ(e->cmd[e->cid].arg[0], "history"))
		history_print(e);
	else if (ft_strequ(e->cmd[e->cid].arg[0], "hash"))
		builtin_hash(e);
	else if (!process_builtin_2(e))
		return (0);
	return (1);
}

int		process_builtin_2(t_env *e)
{
	if (ft_strequ(e->cmd[e->cid].arg[0], "alias"))
		builtin_alias(e);
	else if (ft_strequ(e->cmd[e->cid].arg[0], "unalias"))
		builtin_unalias(e);
	else
		return (0);
	return (1);
}
