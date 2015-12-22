/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/10 18:58:17 by pbourrie          #+#    #+#             */
/*   Updated: 2015/12/17 22:15:51 by pbourrie         ###   ########.fr       */
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
		if (condi != SEP_PIPE)
			e->cmd_pgid = 0;
		if (redirec_open(e)
			&& ((condi != SEP_AND && condi != SEP_OR)
				|| (condi == SEP_AND && !e->status)
				|| (condi == SEP_OR && e->status)))
		{
			if (!process_builtin(e))
//			{
				process_bin(e, e->var);
				if (e->cmd[e->cid].status)
				{
//					ft_printf("1 ->%ld\n", e->cid);
					redirec_close(e, e->cid);
				}
				process_wait_list(e);
//			}
//			ft_printf("status %ld->%ld\n", e->cid, e->cmd[e->cid].status);
		}
		e->cid++;
	}
	e->carg = NULL;
}

void	process_wait_list(t_env *e)
{
	if (e->nb_cmd > e->cid + 1)
	{
		if (e->cmd[e->cid + 1].condi == SEP_PIPE)
		{
//			ft_printf("NOOOO %ld\n", e->cid);
			return ;
		}
	}
	
	while (e->wait_cid <= e->cid)
	{
		if (e->cmd[e->wait_cid].status)
			process_wait(e, e->cmd[e->wait_cid].pid, 0);
		else if (e->cmd[e->wait_cid + 1].condi != SEP_PIPE)
		{
			tcsetpgrp(0, getpid());
//			ft_printf("YEAH22\n");
		}
		if (!e->cmd[e->wait_cid].status || !e->cmd[e->wait_cid].piped)
		{
//			ft_printf("2 ->%ld\n", e->wait_cid);
			e->cmd[e->wait_cid].piped = 1;
			redirec_close(e, e->wait_cid);
		}
		e->wait_cid++;
	}
}

void	process_wait(t_env *e, int pid, int job)
{
	int		ret;

	ret = 0;
	waitpid(pid, &ret, WUNTRACED);
//	ft_printf("TERMINATED %ld\n", pid);
	if (e->wait_cid == e->cid || job)
	{
//		ft_printf("YEAH! %ld\n", pid);
		tcsetpgrp(0, getpid());
	}

	if (WIFSIGNALED(ret))
	{
		if (ret != SIGINT)
			put_sig_error(ret, e->cmd[e->wait_cid].arg[0], e->cmd[e->cid].fd_err);
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
			put_error(ERRNOENT, NULL, cmd, e->cmd[e->cid].fd_err);
		else
			put_error(ERRNOCMD, NULL, cmd, e->cmd[e->cid].fd_err);
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
		if (e->cmd[e->cid].condi != SEP_PIPE || e->cmd_pgid == 0)
			e->cmd_pgid = child;
//		process_setpgid(e);
//		ft_printf("exec : %s  %ld\n", cmd_path, child);
		e->cmd[e->cid].status = 1;

	}
	else if (child == 0)
	{
//		ft_printf("TCSET\n");
		process_setpgid(e);
		tcsetpgrp(0, getpid());
		redirec_assign(e);

		if (execve(cmd_path, e->cmd[e->cid].arg, env) == -1)
		{
			if (ft_get_file_mode(cmd_path) % 2 == 0 
				|| ft_get_file_type(cmd_path) != '-')
				put_error(ERRACCES, NULL, e->cmd[e->cid].arg[0], e->cmd[e->cid].fd_err);
			else
				put_error(ERREXEFORM, NULL, e->cmd[e->cid].arg[0], e->cmd[e->cid].fd_err);
			exit(126);
		}
	}
}

void	process_setpgid(t_env *e)
{
//		ft_printf("setpgid(%ld, %ld);\n", e->cmd[e->cid].pid, e->cmd_pgid);
	if (setpgid(e->cmd[e->cid].pid, e->cmd_pgid))
	{
		perror("");
		ft_printf("setpgid(%ld, %ld);\n", e->cmd[e->cid].pid, e->cmd_pgid);
	}
//		ft_putendl_fd("setpgid 2 fail", 2);
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

