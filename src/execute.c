/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/10 18:58:17 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 22:15:38 by pbourrie         ###   ########.fr       */
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
		e->carg = e->cmd[e->cid].arg;
		condi = e->cmd[e->cid].condi;
		if (redirec_open(e)
			&& ((condi != SEP_AND && condi != SEP_OR)
				|| (condi == SEP_AND && !e->status)
				|| (condi == SEP_OR && e->status)))
		{
			if (!process_builtin(e))
			{
				process_bin(e, e->var);
//				if (e->status != 127) // GROS POBEME
				process_wait_list(e);
			}
		}
		e->cid++;
	}
	e->carg = NULL;
}

void	process_wait_list(t_env *e)
{
	redirec_close(e);
	if (e->nb_cmd > e->cid + 1)
	{
		if (e->cmd[e->cid + 1].condi == SEP_PIPE)
		{
//			ft_printf("NOOOO %ld\n", e->cid);
			return ;
		}
	}

	while (e->wait_cid <= e->cid)
		process_wait(e, e->cmd[e->wait_cid++].pid, 0);
}

int		process_builtin(t_env *e)
{
	if (ft_strequ(e->cmd[e->cid].arg[0], "cd"))
		builtin_cd(e);
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
//	else if (ft_strequ(e->cmd[0], "kill"))
//	{
//		jobs_exit(e);
//		if (e->jobs)
//			kill(e->jobs->pid, ft_atoi(e->cmd[1]));
//	}
	else
		return (0);
	return (1);
}

void	process_bin(t_env *e, char **env)
{
	char	*cmd_path;
	char	*cmd;

	cmd = e->cmd[e->cid].arg[0];
	cmd_path = get_cmd_path(e, cmd);
	if (ft_strchr(cmd, '/') && ft_get_file_type(cmd) != -1)
		cmd_path = ft_strdup(cmd);
	if (cmd_path != NULL)
	{
		process_fork(e, cmd_path, env);
		free(cmd_path);
	}
	else
	{
		e->status = 127;
		if (ft_strchr(cmd, '/'))
			put_error(ERRNOENT, NULL, cmd);
		else
			put_error(ERRNOCMD, NULL, cmd);
	}
}

void	process_fork(t_env *e, char *cmd_path, char **env)
{
	int		child;

	if ((child = fork()) == -1)
		return ;
	if (child > 0)
	{
		e->cmd[e->cid].pid = child;
		process_setpgid(e);
		tcsetpgrp(0, child);
	}
	else if (child == 0)
	{

		redirec_assign(e);
		if (execve(cmd_path, e->cmd[e->cid].arg, env) == -1)
		{
			if (ft_get_file_mode(cmd_path) % 2 == 0 
				|| ft_get_file_type(cmd_path) != '-')
				put_error(ERRACCES, NULL, e->cmd[e->cid].arg[0]);
			else
				put_error(ERREXEFORM, NULL, e->cmd[e->cid].arg[0]);
			exit(126);
		}
	}
}

void	process_wait(t_env *e, int pid, int job)
{
	int		ret;

	ret = 0;
	waitpid(pid, &ret, WUNTRACED);
	tcsetpgrp(1, getpid());
	if (WIFSIGNALED(ret))
	{
		if (ret != SIGINT)
			put_sig_error(ret, e->cmd[e->cid].arg[0]);
		e->status = (WTERMSIG(ret)) + 128;
	}
	else if (WIFSTOPPED(ret))
	{
		if (WSTOPSIG(ret) == SIGTSTP)
		{
			jobs_add(e, pid);
		}
	}
	else
		e->status = WEXITSTATUS(ret);
	if (!WIFSTOPPED(ret) && job)
		jobs_remove(e, pid);
}

void	process_setpgid(t_env *e)
{
	if (e->cmd[e->cid].condi == SEP_PIPE)
	{
		if (setpgid(e->cmd[e->cid].pid, e->cmd_pgid))
			ft_putendl_fd("setpgid fail", 2);
	}
	else
	{
		e->cmd_pgid = e->cmd[e->cid].pid;
		if (setpgid(e->cmd[e->cid].pid, e->cmd_pgid))
			ft_putendl_fd("setpgid fail", 2);
	}
}
