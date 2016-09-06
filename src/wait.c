/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 15:54:41 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/06 01:59:15 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	process_wait(t_env *e, int pid, int job)
{
	int		ret;

	if (!e->sub && e->background_cmd && !job)
	{
		jobs_add(e, pid);
		return ;
	}
	ret = 0;

	waitpid(pid * -1, &ret, WUNTRACED);
//	perror("");
//	if (e->wait_cid == e->cid || job)
//	ft_printf("ICI\n");
	if (WIFSTOPPED(ret) && !e->sub && WSTOPSIG(ret) == SIGTSTP)
		usleep(400);

	if (!e->sub)
		tcsetpgrp(0, getpgrp());
//	ft_printf("front=%d\n", tcgetpgrp(0));
	if (!e->sub)
		term_restore(e);
	process_wait_status(e, ret, pid, job);
}

void	process_wait_status(t_env *e, int status, int pid, int job)
{
	if (WIFSIGNALED(status))
	{
		if (status != SIGINT && !e->sub)
			process_wait_error(e, status, job);
		else if (!e->sub)
			ft_putchar('\n');
		e->status = (WTERMSIG(status)) + 128;
	}
	else if (WIFSTOPPED(status) && !e->sub)
	{

		if (WSTOPSIG(status) == SIGTSTP)
		{
			if (!job)
				jobs_add(e, pid);

		usleep(400);
			tcsetpgrp(0, getpid());
			term_restore(e);

			jobs_put_job_status(e, pid, "suspended");
			if (isatty(e->fd_in) && job)
			{
				gen_prompt(e, NULL);
				print_prompt(e);
			}

		}
		else if (WSTOPSIG(status) == SIGTTOU && job)
		{
			jobs_put_job_status(e, pid, "suspended (tty output)");
			if (isatty(e->fd_in))
			{
				gen_prompt(e, NULL);
				print_prompt(e);
			}
		}
		else if (WSTOPSIG(status) == SIGTTIN && job)
		{
			jobs_put_job_status(e, pid, "suspended (tty input)");
			if (isatty(e->fd_in))
			{
				gen_prompt(e, NULL);
				print_prompt(e);
			}
		}
	}
	else
	{
		e->status = WEXITSTATUS(status);

		if (job)
		{
//		ft_printf("ICI sign=%d\n", WSTOPSIG(status));
			tcsetpgrp(0, getpid());
			term_restore(e);
		}
	}
	if (!WIFSTOPPED(status) && job && !e->sub)
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
