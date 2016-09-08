/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/09 01:19:58 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		pipe_new(t_env *e, t_redir *redir)
{
	if ((pipe(e->cmd[e->cid].pipe) == -1))
	{
		ft_putstr_fd("Error : can't create pipe ", 2);
		redir->type = R_PIPENOT;
		return (0);
	}
	return (1);
}

void	pipe_assign(t_env *e)
{
	int		cid;

	cid = 0;
	if (e->cid > 0)
		dup2(e->cmd[e->cid - 1].pipe[0], 0);
	if (e->cid + 1 != e->nb_cmd)
		dup2(e->cmd[e->cid].pipe[1], 1);
	while (e->nb_cmd - 1 > cid)
	{
		close(e->cmd[cid].pipe[0]);
		close(e->cmd[cid].pipe[1]);
		cid++;
	}
}

void	pipe_close(t_env *e, int cid)
{
	close(e->cmd[cid - 1].pipe[0]);
	close(e->cmd[cid - 1].pipe[1]);
}
