/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 19:30:05 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/01 01:04:38 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free_env(t_env *e)
{
	free_history(e);
	free_cmd(e);
	free_path_and_env(e);
	free_hash_table(e);
	if (e->line)
		free(e->line);
	if (e->home)
		free(e->home);
	if (e->home_dir)
		free(e->home_dir);
	if (e->pwd)
		free(e->pwd);
	if (e->clipboard)
		free(e->clipboard);
	if (e->histo_file)
		free(e->histo_file);
	if (e->term_name)
		free(e->term_name);
	if (e->term)
		free(e->term);
	if (e->term_back)
		free(e->term_back);
	free(e);
}

void	free_path_and_env(t_env *e)
{
	int		i;

	if (e->path)
	{
		i = 0;
		while (e->path[i])
			free(e->path[i++]);
		free(e->path);
	}
	if (e->var)
	{
		i = 0;
		while (e->var[i])
			free(e->var[i++]);
		free(e->var);
	}
}

void	free_history(t_env *e)
{
	t_histo	*cur;
	t_histo	*tofree;

	cur = e->histo_begin;
	while (cur)
	{
		tofree = cur;
		cur = cur->down;
		if (tofree->line)
			free(tofree->line);
		free(tofree);
	}
}

void	kill_jobs(t_env *e)
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
		tmp = job;
		job = job->next;
		if (tmp->name)
			free(tmp->name);
		free(tmp);
	}
	e->jobs_lst = NULL;
	e->job = NULL;
}

void	free_hash_table(t_env *e)
{
	int			i;
	t_hash_b	*cur;
	t_hash_b	*tmp;

	i = -1;
	while (++i < e->hash_total)
	{
		cur = e->hash_t[i];
		while (cur)
		{
			tmp = cur;
			cur = cur->next;
			free(tmp->key);
			free(tmp->val);
			free(tmp);
		}
	}
	free(e->hash_t);
}
