/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/08 22:39:30 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	free_cmd(t_env *e)
{
	int	i;
	int	i2;

	i = -1;
	i2 = 0;
	while (e->nb_cmd > ++i)
	{
		while (e->cmd[i].arg && e->cmd[i].arg[i2])
		{
			free(e->cmd[i].arg[i2]);
			e->cmd[i].arg[i2] = NULL;
			i2++;
		}
		if (e->cmd[i].arg)
			free(e->cmd[i].arg);
		free_cmd_redirec(e, i);
		free_heredoc(e, i);
		e->cmd[i].arg = NULL;
		i2 = 0;
	}
	if (e->cmd[0].name)
		free(e->cmd[0].name);
	free(e->cmd);
	e->cmd = NULL;
	e->nb_cmd = 0;
}

void	free_cmd_redirec(t_env *e, int i)
{
	t_redir	*redir;
	t_redir	*tmp;

	redir = e->cmd[i].redir;
	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
}

void	free_heredoc(t_env *e, int cid)
{
	t_hdoc	*hdoc;
	t_hdoc	*tmp;

	hdoc = e->cmd[cid].hdoc;
	if (!hdoc)
		return ;
	while (hdoc)
	{
		tmp = hdoc;
		hdoc = hdoc->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
	e->cmd[cid].hdoc = NULL;
}
