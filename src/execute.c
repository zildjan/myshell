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

void	pipe_new(t_env *e)
{
	if (e->cid + 1 < e->nb_cmd)
	{
		pipe(e->cmd[e->cid].pipe);
//		ft_printf("un pipe\n");
	}
}

void	pipe_assign(t_env *e)
{
	if (e->cid > 0)
	{
//		ft_printf("assign <- %ld depuis %ld\n", e->cid -1, e->cid);
		close(e->cmd[e->cid - 1].pipe[1]);
		dup2(e->cmd[e->cid - 1].pipe[0], 0);
		close(e->cmd[e->cid - 1].pipe[0]);
	}
	if (e->cid + 1 < e->nb_cmd && e->nb_cmd > 1)
	{
//		ft_printf("assign -> %ld vers %ld\n", e->cid, e->cid +1);
		close(e->cmd[e->cid].pipe[0]);
		dup2(e->cmd[e->cid].pipe[1], 1);
		close(e->cmd[e->cid].pipe[1]);
	}
}

void	pipe_close(t_env *e)
{
	if (e->cid > 0)
	{
//		ft_printf("close pipe\n");
		close(e->cmd[e->cid - 1].pipe[0]);
		close(e->cmd[e->cid - 1].pipe[1]);
	}
}

void	process_cmd(t_env *e)
{
	e->cid = 0;
	while (e->nb_cmd > e->cid)
	{
		e->carg = e->cmd[e->cid].arg;
		pipe_new(e);
		if (!process_builtin(e))
			process_bin(e, e->var);
		e->cid++;
	}
	e->carg = NULL;
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
		if (setpgid(child, child))
			ft_putendl_fd("setpgid fail", 2);
		tcsetpgrp(0, child);
		pipe_close(e);
		process_wait(e, child, 0);
	}
	else if (child == 0)
	{
		if (setpgid(0, 0))
			ft_putendl_fd("setpgid fail", 2);
		pipe_assign(e);
		if (execve(cmd_path, e->cmd[e->cid].arg, env) == -1)
		{
			if (ft_get_file_mode(cmd_path) % 2 == 0 
				|| ft_get_file_type(cmd_path) != '-')
				put_error(ERRACCES, NULL, e->cmd[e->cid].arg[0]);
			else
				put_error(ERREXEFORM, NULL, e->cmd[e->cid].arg[0]);
			exit(0);
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
