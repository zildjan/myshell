/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 00:14:27 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/09 00:16:44 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	jobs_update_status(t_env *e)
{
	int		status;
	t_job	*job;
	pid_t	pid;

	job = e->jobs_lst;
	while (job)
	{
		pid = waitpid(job->pgid, &status, WUNTRACED | WNOHANG);
		if (pid > 0)
		{
			process_wait_status(e, status, pid, pid);
		}
		job = job->next;
	}
}

void	jobs_put_job_status(t_env *e, pid_t pgid, char nl, char *status)
{
	t_job	*job;

	job = jobs_find(e, pgid, 0);
	if (!job)
		return ;
	ft_putstr("\r");
	if (nl)
		ft_putstr("                                              \n");
	ft_printf("[%d]  - %d %s  %s\n", job->id, pgid, status, job->name);
	if (!nl)
	{
		if (isatty(e->fd_in))
		{
			gen_prompt(e, NULL);
			print_prompt(e);
		}
	}
}

t_job	*jobs_find(t_env *e, pid_t pgid, int id)
{
	t_job	*job;

	job = e->jobs_lst;
	while (job)
	{
		if (pgid)
		{
			if (job->pgid == pgid)
				return (job);
		}
		else
		{
			if (job->id == id)
				return (job);
		}
		job = job->next;
	}
	return (NULL);
}

void	jobs_add(t_env *e, pid_t pgid)
{
	t_job	*new;
	t_job	*tmp;
	int		id;

	if ((id = jobs_get_new_id(e, pgid)) != -1)
	{
		tmp = e->jobs_lst;
		while (tmp && tmp->next)
			tmp = tmp->next;
		new = (t_job*)ft_memalloc(sizeof(t_job));
		new->pgid = pgid;
		new->id = id;
		new->name = ft_strdup(e->cmd[0].name);
		new->next = NULL;
		e->job = new;
		if (!e->jobs_lst)
			e->jobs_lst = new;
		else
			tmp->next = new;
	}
}

int		jobs_get_new_id(t_env *e, pid_t pgid)
{
	t_job	*tmp;
	int		i;

	tmp = e->jobs_lst;
	i = 0;
	while (tmp)
	{
		if (tmp->pgid == pgid)
			return (-1);
		i = tmp->id;
		tmp = tmp->next;
	}
	i++;
	return (i);
}
