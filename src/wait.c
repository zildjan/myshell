/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 15:54:41 by pbourrie          #+#    #+#             */
/*   Updated: 2016/07/21 02:23:09 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	process_wait(t_env *e, int pid, int job)
{
	int		ret;

	ret = 0;
	waitpid(pid, &ret, WUNTRACED);
//	perror("");
//	if (e->wait_cid == e->cid || job)
	if (!e->sub)
		tcsetpgrp(0, getpid());
	if (!e->sub)
		term_restore(e);
	if (WIFSIGNALED(ret))
	{
		if (ret != SIGINT && !e->sub)
			process_wait_error(e, ret, job);
		else if (!e->sub)
			ft_putchar('\n');
		e->status = (WTERMSIG(ret)) + 128;
	}
	else if (WIFSTOPPED(ret) && !e->sub)
	{
		if (WSTOPSIG(ret) == SIGTSTP)
			jobs_add(e, pid);
	}
	else
		e->status = WEXITSTATUS(ret);
	if (!WIFSTOPPED(ret) && job && !e->sub)
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
		fd = e->cmd[e->cid].fd_err;
		name = e->cmd[e->cid].arg[0];
	}
	put_sig_error(ret, name, fd);
}
