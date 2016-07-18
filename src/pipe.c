/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/07/18 01:18:42 by pbourrie         ###   ########.fr       */
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
//	ft_printf("pipe=%d_%d\n", e->cmd[e->cid].pipe[0], e->cmd[e->cid].pipe[1]);
	return (1);
}

void	pipe_assign(t_env *e, t_redir *redir)
{
	int		cid;
/*
	if (redir->type == R_PIPEIN)
	{

		dup2(e->cmd[e->cid - 1].pipe[0], 0);
		close(e->cmd[e->cid - 1].pipe[1]);
		close(e->cmd[e->cid - 1].pipe[0]);
	}
	else if (redir->type == R_PIPEOUT)
	{

		dup2(e->cmd[e->cid].pipe[1], 1);
		close(e->cmd[e->cid].pipe[0]);
		close(e->cmd[e->cid].pipe[1]);
	}

//*/
	(void)redir;
	cid = 0;
//	if (redir->type == R_PIPEIN)
//		dup2(e->cmd[e->cid - 1].pipe[0], 0);
//	else if (redir->type == R_PIPEOUT)
//		dup2(e->cmd[e->cid].pipe[1], 1);

	if (e->cid > 0)
		dup2(e->cmd[e->cid - 1].pipe[0], 0);
	if (e->cid + 1 != e->nb_cmd)
		dup2(e->cmd[e->cid].pipe[1], 1);

	while (e->nb_cmd - 1 > cid)
	{
		close(e->cmd[cid].pipe[0]);
		if (close(e->cmd[cid].pipe[1]))
			perror("ICI");

		cid++;
	}
// */
}

void	pipe_close(t_env *e, int cid)
{
	close(e->cmd[cid - 1].pipe[0]);
	close(e->cmd[cid - 1].pipe[1]);
}
