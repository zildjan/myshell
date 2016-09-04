/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/13 22:16:21 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/04 18:42:18 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	jobs_update_status(t_env *e)
{
	int		status;
	t_job	*job;
	int		pid;

	job = e->jobs_lst;
//	ft_printf("ICI\n");
	while (job)
	{
		pid = waitpid (job->pgid, &status, WUNTRACED | WNOHANG);
		if (pid > 0)
		{
//			ft_printf("pid=%d status=%d\n", pid, status);
			process_wait_status(e, status, pid, pid);
//			tcsetpgrp(0, getpid());
		}
		job = job->next;
	}
}

void	jobs_add(t_env *e, int pid)
{
	t_job	*new;
	t_job	*tmp;
	int		id;

//	ft_printf("\n suspended  \n");
	if ((id = jobs_count(e, pid)) != -1)
	{

		tmp = e->jobs_lst;
		while (tmp && tmp->next)
			tmp = tmp->next;

		new = (t_job*)ft_memalloc(sizeof(t_job));
		new->pgid = pid; ///////////
		new->id = id + 1;
//x	ft_printf("ICI\n");
		new->name = ft_strdup(e->carg[0]);
		new->next = NULL;

		e->job = new;
		if (!e->jobs_lst)
			e->jobs_lst = new;
		else
			tmp->next = new;
	}
//	term_restore(e);
//	tcsetpgrp(0, getpid());
	ft_printf("\n[%d]  - %d suspended  %s\n", e->job->id, pid, e->job->name);

}

void	jobs_continue(t_env *e, int fg)
{
	char	*name;

	e->job = e->jobs_lst;
	while (e->job && e->job->next)
		e->job = e->job->next;
	if (!e->jobs_lst)
	{
		if (fg)
			ft_putendl_fd("fg: no current job", 2);
		else
			ft_putendl_fd("bg: no current job", 2);
		return ;
	}
	name = e->job->name;
	ft_printf("[%d]  - %d continued  %s\n", e->job->id, e->job->pgid, name);

	if (fg)
	{
//		ft_printf("ICI\n");
		term_restore_back(e);
		tcsetpgrp(0, e->job->pgid);
	}
	killpg(e->job->pgid, SIGCONT);
//	process_wait(e, e->job->pgid, 1);
}

void	jobs_remove(t_env *e, int pid)
{
	t_job	*job;
	t_job	*pre_job;

	pre_job = NULL;
	job = e->jobs_lst;
	while (job && job->pgid != pid)
	{
		pre_job = job;
		job = job->next;
	}
	if (!job)
		return ;
	killpg(job->pgid, SIGINT);
	ft_printf("\n[%d]  - %d Done  %s\n", e->job->id, pid, e->job->name);
	if (isatty(e->fd_in))
	{
		gen_prompt(e, NULL);
		print_prompt(e);
	}
	if (pre_job)
		pre_job->next = job->next;
	else
		e->jobs_lst = NULL;
	if (job->name)
		free(job->name);
	free(job);
	if (!e->job)
		e->job = pre_job;
}

void	jobs_list(t_env *e)
{
	t_job	*job;
	int		i;

	i = 0;
	job = e->jobs_lst;
	while (job)
	{
		i++;
		ft_printf("[%d]  %d - %s\n", job->id, job->pgid, job->name);
		job = job->next;
	}
}

int		jobs_count(t_env *e, int pid)
{
	t_job	*tmp;
	int		i;

	tmp = e->jobs_lst;
	i = 0;
	while (tmp)
	{
		if (tmp->pgid == pid)
			return (-1);
		tmp = tmp->next;
		i++;
	}
	return (i);
}
