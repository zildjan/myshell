/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/13 22:16:21 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 22:35:24 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	jobs_add(t_env *e, int pid)
{
	t_job	*new;
	t_job	*tmp;
	int		id;

	if ((id = jobs_count(e, pid)) != -1)
	{
		tmp = e->jobs_lst;
		while (tmp && tmp->next)
			tmp = tmp->next;
		new = (t_job*)ft_memalloc(sizeof(t_job));
		new->pid = pid;
		new->pgid = e->cmd_pgid;
		new->id = id + 1;
		new->name = ft_strdup(e->carg[0]);
		new->next = NULL;
		e->job = new;
		if (!e->jobs_lst)
			e->jobs_lst = new;
		else
			tmp->next = new;
	}
	ft_printf("\n[%ld]  - %ld suspended  %s\n", e->job->id, pid, e->job->name);
}

void	jobs_continue(t_env *e)
{
	e->job = e->jobs_lst;
	while (e->job && e->job->next)
		e->job = e->job->next;
	if (!e->jobs_lst)
	{
		ft_putendl_fd("fg: no current job", 2);
		return ;
	}
	ft_printf("[%ld]  - %ld continued  %s\n", e->job->id, e->job->pgid, e->job->name);
//	ft_putendl("ICI");
//	ft_printf("pg=%ld\n", e->job->pgid);
	tcsetpgrp(0, e->job->pgid);
	if (!killpg(e->job->pgid, SIGCONT))
		process_wait(e, e->job->pid, 1);
	else
		jobs_remove(e, e->job->pgid);
}

void	jobs_remove(t_env *e, int pid)
{
	t_job	*job;
	t_job	*pre_job;

	pre_job = NULL;
	job = e->jobs_lst;
	while (job && job->pid != pid)
	{
		pre_job = job;
		job = job->next;
	}
	if (!job)
		return ;
	killpg(job->pgid, SIGINT);
//	ft_printf("removed -> %s\n", job->name);
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
		ft_printf("[%ld]  %ld - %s\n", job->id, job->pgid, job->name);
		job = job->next;
	}
}

void	jobs_exit(t_env *e)
{
	t_job	*job;
	t_job	*tmp;
	int		i;
	int		ret;

	i = 0;
	job = e->jobs_lst;
	while (job)
	{
		i++;
		kill(job->pgid, SIGKILL);
		waitpid(job->pgid, &ret, WUNTRACED);
//		ft_printf("[%ld]  killed  %ld - %s\n", job->id, job->pid, job->name);
		tmp = job;
		job = job->next;
		if (tmp->name)
			free(tmp->name);
		free(tmp);
	}
	e->jobs_lst = NULL;
	e->job = NULL;
}

int		jobs_count(t_env *e, int pid)
{
	t_job	*tmp;
	int		i;

	tmp = e->jobs_lst;
	i = 0;
	while (tmp)
	{
		if (tmp->pid == pid)
			return (-1);
		tmp = tmp->next;
		i++;
	}
	return (i);
}
