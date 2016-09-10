/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/13 22:16:21 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/10 02:35:00 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		jobs_continue_getjob(t_env *e, int fg, int id)
{
	if (e->carg[1] != NULL)
	{
		if (!ft_strcheck(e->carg[1], ft_isdigit))
		{
			if (fg)
				ft_putstr_fd("fg: no such job: ", 2);
			else
				ft_putstr_fd("bg: no such job: ", 2);
			ft_putendl_fd(e->carg[1], 2);
			return (0);
		}
		id = ft_atoi(e->carg[1]);
		if (id)
			e->job = jobs_find(e, 0, id);
		if (e->job == NULL)
		{
			if (fg)
				ft_putstr_fd("fg: no such job: ", 2);
			else
				ft_putstr_fd("bg: no such job: ", 2);
			ft_putendl_fd(e->carg[1], 2);
			return (0);
		}
	}
	return (1);
}

void	jobs_continue(t_env *e, int fg)
{
	if (!jobs_continue_getjob(e, fg, 0))
		return ;
	if (!e->job)
	{
		e->job = e->jobs_lst;
		while (e->job && e->job->next)
			e->job = e->job->next;
	}
	if (!e->job)
	{
		if (fg)
			ft_putendl_fd("fg: no current job", 2);
		else
			ft_putendl_fd("bg: no current job", 2);
		return ;
	}
	ft_printf("[%d]  - %d continued  %s\n",
			e->job->id, e->job->pgid, e->job->name);
	if (fg)
	{
		term_restore_back(e);
		term_set_tcpgid(e, e->job->pgid);
	}
	killpg(e->job->pgid, SIGCONT);
}

void	jobs_remove(t_env *e, pid_t pgid)
{
	t_job	*job;
	t_job	*pre_job;

	pre_job = NULL;
	job = e->jobs_lst;
	while (job && job->pgid != pgid)
	{
		pre_job = job;
		job = job->next;
	}
	if (!job)
		return ;
	killpg(job->pgid, SIGINT);
	jobs_remove_notif(e, job);
	if (pre_job)
		pre_job->next = job->next;
	else
		e->jobs_lst = job->next;
	if (job->name)
		free(job->name);
	free(job);
	e->job = e->jobs_lst;
	while (e->job && e->job->next)
		e->job = e->job->next;
}

void	jobs_remove_notif(t_env *e, t_job *job)
{
	if (!e->status && e->last_job != job->pgid)
		ft_printf("\n\r[%d]  - %d Done  %s", job->id, job->pgid, job->name);
	else if (e->status < 126 && e->last_job != job->pgid)
		ft_printf("\n\r[%d]  - %d exit %d  %s",
				job->id, job->pgid, e->status, job->name);
	ft_putchar('\n');
	if (isatty(e->fd_in))
	{
		gen_prompt(e, NULL);
		print_prompt(e);
	}
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
