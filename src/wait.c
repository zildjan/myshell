/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 15:54:41 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/10 16:09:49 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	process_wait_list(t_env *e)
{
	if (e->nb_cmd > e->cid + 1)
	{
		if (e->cmd[e->cid + 1].condi == SEP_PIPE)
		{
			return ;
		}
	}
	while (e->wait_cid <= e->cid)
	{
		if (e->cmd[e->wait_cid].status)
			process_wait(e, e->cmd[e->wait_cid].pid, 0);
		else if (e->cmd[e->wait_cid + 1].condi != SEP_PIPE)
			tcsetpgrp(0, getpid());
		if (!e->cmd[e->wait_cid].status || !e->cmd[e->wait_cid].piped)
		{
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
	if (e->wait_cid == e->cid || job)
		tcsetpgrp(0, getpid());
	term_restore(e);
	if (WIFSIGNALED(ret))
	{
		if (ret != SIGINT)
			process_wait_error(e, ret, job);
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

void	process_wait_error(t_env *e, int ret, int job)
{
	int		fd;
	char	*name;

	if (job)
	{
		fd = 2;
		name = e->job->name;
	}
	else
	{
		fd = e->cmd[e->wait_cid].fd_err;
		name = e->cmd[e->wait_cid].arg[0];
	}
	put_sig_error(ret, name, fd);
}
