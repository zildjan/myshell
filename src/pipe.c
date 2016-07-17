/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/07/17 02:33:19 by pbourrie         ###   ########.fr       */
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
	ft_printf("pipe= %d\n", e->cmd[e->cid].pipe[0]);
	return (1);
}

void	pipe_assign(t_env *e, t_redir *redir)
{
	int		cid;
	if (redir->type == R_PIPEIN)
	{
		close(e->cmd[e->cid - 1].pipe[1]);
		dup2(e->cmd[e->cid - 1].pipe[0], 0);
		close(e->cmd[e->cid - 1].pipe[0]);
	}
	else if (redir->type == R_PIPEOUT)
	{
		close(e->cmd[e->cid].pipe[0]);
		dup2(e->cmd[e->cid].pipe[1], 1);
		close(e->cmd[e->cid].pipe[1]);
	}

//*/

	cid = e->cid;
//	if (redir->type == R_PIPEIN)
//		dup2(e->cmd[e->cid - 1].pipe[0], 0);
//	else if (redir->type == R_PIPEOUT)
//		dup2(e->cmd[e->cid].pipe[1], 1);

	while (e->nb_cmd > cid)
	{
		if (e->cid != cid && e->cid - 1 != cid && e->cid + 1 != cid)
		{
			close(e->cmd[cid].pipe[0]);
			close(e->cmd[cid].pipe[1]);
		}
		cid++;
	}
// */
}

void	pipe_close(t_env *e, int cid)
{
	close(e->cmd[cid - 1].pipe[0]);
	close(e->cmd[cid - 1].pipe[1]);
}
