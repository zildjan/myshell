/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/13 22:16:21 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/05 02:15:08 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	jobs_update_status(t_env *e)
{
	int		status;
	t_job	*job;
	int		pid;


	if (!e->fg)
		return ;
	job = e->jobs_lst;
//	ft_printf("ICI\n");
	while (job)
	{
		pid = waitpid (job->pgid, &status, WUNTRACED | WNOHANG);
		if (pid > 0)
		{
//			ft_printf("\n\npid=%d status=%d\n\n", pid, status);
			process_wait_status(e, status, pid, pid);
//		term_restore(e);
//			tcsetpgrp(0, getpid());
		}
		job = job->next;
	}
}

t_job	*jobs_find(t_env *e, int pid, int id)
{
	t_job	*job;

	job = e->jobs_lst;
	while (job)
	{
		if (pid)
		{
			if (job->pgid == pid)
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

void	jobs_add(t_env *e, int pid)
{
	t_job	*new;
	t_job	*tmp;
	int		id;

//	ft_printf("\n suspended  \n");
	if ((id = jobs_get_new_id(e, pid)) != -1)
	{

		tmp = e->jobs_lst;
		while (tmp && tmp->next)
			tmp = tmp->next;

		new = (t_job*)ft_memalloc(sizeof(t_job));
		new->pgid = pid; ///////////
		new->id = id;
		new->name = ft_strdup(e->carg[0]);
		new->next = NULL;

		e->job = new;
		if (!e->jobs_lst)
			e->jobs_lst = new;
		else
			tmp->next = new;
	}
//	ft_printf("\n[%d]  - %d suspended  %s\n", e->job->id, pid, e->job->name);
}

void	jobs_continue(t_env *e, int fg)
{
	char	*name;
	int		id;

	if (e->carg[1] != NULL)
	{
		if (!ft_strcheck(e->carg[1], ft_isdigit))
		{
			if (fg)
				ft_putstr_fd("fg: no such job: ", 2);
			else
				ft_putstr_fd("bg: no such job: ", 2);
			ft_putendl_fd(e->carg[1], 2);
			return ;
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
			return ;
		}
	}

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

	name = e->job->name;
	ft_printf("[%d]  - %d continued  %s\n", e->job->id, e->job->pgid, name);

	if (fg)
	{
		term_restore_back(e);
		tcsetpgrp(0, e->job->pgid);
	}
	e->fg = 0;
	killpg(e->job->pgid, SIGCONT);
//	ft_printf("ICI1\n");
	process_wait(e, e->job->pgid, 1);
	e->fg = 1;



	struct termios *test2;
	test2 = ft_memalloc(sizeof(struct termios));
	tcgetattr(0, test2);
	if (ft_memcmp(test2, e->term, sizeof(struct termios)))
	{
//		ft_printf("YOUPI !");
		tcsetattr(0, TCSADRAIN, e->term);
	}
	free(test2);
// */


//	ft_printf("ICI2\n");
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
		e->jobs_lst = job->next;
	if (job->name)
		free(job->name);
	free(job);

	e->job = e->jobs_lst;
	while (e->job && e->job->next)
		e->job = e->job->next;
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

int		jobs_get_new_id(t_env *e, int pid)
{
	t_job	*tmp;
	int		i;

	tmp = e->jobs_lst;
	i = 0;
	while (tmp)
	{
		if (tmp->pgid == pid)
			return (-1);
		i = tmp->id;
		tmp = tmp->next;
	}
	i++;
	return (i);
}
