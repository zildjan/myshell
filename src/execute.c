/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/10 18:58:17 by pbourrie          #+#    #+#             */
/*   Updated: 2016/07/17 02:23:05 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	process_cmd(t_env *e)
{
	int		condi;

//	ft_printf("nb_cmd=%d\n", e->nb_cmd);

	if (e->nb_cmd > 1)
	{
		process_piped_cmd(e);
		return ;
	}

	e->cid = 0;

//		ft_printf("condi=%d\n", e->cmd[e->cid].condi);
	e->carg = e->cmd[e->cid].arg;
	condi = e->cmd[e->cid].condi;
	if (redirec_open_all(e)
		&& ((condi != SEP_AND && condi != SEP_OR)
			|| (condi == SEP_AND && !e->status)
			|| (condi == SEP_OR && e->status)))
	{
		if (!process_builtin(e))
			process_bin(e, e->var, 1);
	}
	if (e->cmd[e->cid].status)
		process_wait(e, e->cmd[e->cid].pid, 0);
//	tcsetpgrp(0, getpid());
	redirec_close(e, e->cid);
	e->carg = NULL;
}

void	process_piped_cmd(t_env *e)
{
	int		child;
//	int		ret;
	int		dofork;

	e->cid = 0;
	dofork = 1;
	term_restore_back(e);
	child = fork();

	if (child > 0)
	{
		setpgid(child, child);
		tcsetpgrp(0, child);
//		process_wait(e, child, 0);
		process_wait(e, child * (-1), 0);


//		sleep(10);
//	term_restore_back(e);
//	term_restore(e);


// */
//		tcsetpgrp(0, getpid());

	}
	else
	{
		e->sub = 1;
		signal_default();

		while (e->nb_cmd > e->cid)
		{
			e->carg = e->cmd[e->cid].arg;
			if (!redirec_open_all(e))
				ft_printf("ERRRORORORO\n");
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
}

void	process_bin(t_env *e, char **env, int dofork)
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
		if (!e->sub)
			term_restore_back(e);
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

void	process_fork(t_env *e, char *cmd_path, char **env, int dofork)
{
	int		child;

	child = 0;
	if (dofork)
		child = fork();
	if (child > 0 || dofork == 0)
	{
		e->cmd[e->cid].pid = child;
		e->cmd[e->cid].status = 1;
		if (!e->sub)
		{
			setpgid(child, child);
			tcsetpgrp(0, child);
		}
	}
	if (child == 0)
	{
//		e->sub = 1;
		signal_default();
		if (!e->sub)
		{
//			setpgid(e->cmd[e->cid].pid, e->cmd_pgid);
//		ft_printf("ICI\n");
//			tcsetpgrp(0, getpid());

		}

//		tcsetpgrp(0, e->cmd_pgid);
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

void	process_fork_subcmd(t_env *e)
{
//	ft_printf("subcmd='%s'\n", e->cmd[e->cid].arg[0]);

	int		child;

	e->sub = 1;
	child = fork();
	if (child > 0)
	{
		e->cmd[e->cid].pid = child;
//	if (e->cmd[e->cid].condi != SEP_PIPE || e->cmd_pgid == 0)
		e->cmd[e->cid].status = 1;
	}
	else if (child == 0)
	{
		e->sub = 0;
		setpgid(e->cmd[e->cid].pid, getpid());
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
