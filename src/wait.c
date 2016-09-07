/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 15:54:41 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/08 01:45:54 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	process_wait(t_env *e, pid_t pid, int job)
{
	int		ret;

	if (!e->sub && e->background_cmd && !job)
	{
		jobs_add(e, pid);
		return ;
	}
	ret = 0;

	waitpid(pid , &ret, WUNTRACED);


	if (WIFSTOPPED(ret) && !e->sub && WSTOPSIG(ret) == SIGTSTP)
		usleep(400);

	if (!e->sub)
		term_set_tcpgid(e, 0);

	if (!e->sub)
		term_restore(e);
	process_wait_status(e, ret, pid, job);
}

void	process_wait_status(t_env *e, int status, pid_t pid, int job)
{
	if (WIFSIGNALED(status))
	{
		if (status != SIGINT && !e->sub)
			process_wait_error(e, status, job, pid);
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
			term_set_tcpgid(e, 0);
			term_restore(e);

			jobs_put_job_status(e, pid, 1, "suspended");
			if (isatty(e->fd_in) && job)
			{
				gen_prompt(e, NULL);
				print_prompt(e);
			}

		}
		else if (WSTOPSIG(status) == SIGTTOU && job)
		{
			jobs_put_job_status(e, pid, 0, "suspended (tty output)");
			if (isatty(e->fd_in))
			{
				gen_prompt(e, NULL);
				print_prompt(e);
			}
		}
		else if (WSTOPSIG(status) == SIGTTIN && job)
		{
			jobs_put_job_status(e, pid, 0, "suspended (tty input)");
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

		if (job && !e->sub)
		{
//		ft_printf("ICI sign=%d\n", WSTOPSIG(status));
			term_set_tcpgid(e, 0);
			term_restore(e);
		}
	}
	if (!WIFSTOPPED(status) && job && !e->sub)
	{
		jobs_remove(e, pid);
	}
}

void	process_wait_error(t_env *e, int ret, int isjob, pid_t pid)
{
	int		fd;
	char	*name;
	t_job	*job;

	if (isjob)
	{
		fd = 2;
		job = jobs_find(e, pid, 0);
		name = job->name;
		ft_putstr_fd("\r[", 2);
		ft_putnbr_fd(job->id, 2);
		ft_putstr_fd("]  - ", 2);
		ft_putnbr_fd(job->pgid, 2);
	}
	else
	{
		fd = e->cmd[e->cid].fd_err;
		name = e->cmd[e->cid].arg[0];
	}
	put_sig_error(ret, name, fd);
}
