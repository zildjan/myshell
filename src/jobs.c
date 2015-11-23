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

	new = e->jobs;
	while (new)
	{
		if (new->pid == pid)
			return ;
		new = new->next;
	}
	new = (t_job*)ft_memalloc(sizeof(t_job));
	new->pid = pid;
	new->name = ft_strdup(e->cmd[0]);
	new->next = e->jobs;
	e->jobs = new;
}

void	jobs_continue(t_env *e)
{
	if (!e->jobs)
	{
		ft_putendl_fd("fg: no current job", 2);
		return ;
	}
	ft_printf("   --  continued  %s %ld\n", e->jobs->name, e->jobs->pid);
	ft_printf("pg=%ld\n", getpgid(e->jobs->pid));
	if (kill(e->jobs->pid, SIGCONT))
		perror("");
	process_wait(e, e->jobs->pid, 1);
}

void	jobs_remove(t_env *e, int pid)
{
	t_job	*job;

	if (e->jobs->pid != pid)
		return ;
	kill(e->jobs->pid, SIGINT);
	job = e->jobs;
	e->jobs = e->jobs->next;
	if (job->name)
		free(job->name);
	free(job);
}

void	jobs_list(t_env *e)
{
	t_job	*job;
	int		i;

	i = 0;
	job = e->jobs;
	while (job)
	{
		i++;
		ft_printf("[%ld]  %ld - %s\n", i, job->pid, job->name);
		job = job->next;
	}
}
