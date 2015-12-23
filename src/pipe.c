/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/12/17 22:16:03 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"


int 	pipe_new(t_env *e, t_redir *redir)
{
	if ((pipe(e->cmd[e->cid].pipe) == -1))
	{
		ft_putstr_fd("Error : can't create pipe ", 2);
		redir->type = R_PIPENOT;
		return (0);
	}
	
//	ft_printf("new pipe n%ld %ld=%ld\n", e->cid, e->cmd[e->cid].pipe[0], e->cmd[e->cid].pipe[1]);
//	ft_printf("un pipe\n");
	return (1);
}

void	pipe_assign(t_env *e, t_redir *redir)
{
	if (redir->type == R_PIPEIN)
	{
//		ft_printf("assign <- %ld depuis %ld\n", e->cid -1, e->cid);
		close(e->cmd[e->cid - 1].pipe[1]);
		dup2(e->cmd[e->cid - 1].pipe[0], 0);
		close(e->cmd[e->cid - 1].pipe[0]);

	}
	else if (redir->type == R_PIPEOUT)
	{
//		ft_printf("assign -> %ld vers %ld\n", e->cid, e->cid +1);
		close(e->cmd[e->cid].pipe[0]);
		dup2(e->cmd[e->cid].pipe[1], 1);
		close(e->cmd[e->cid].pipe[1]);
	}
}

void	pipe_close(t_env *e, int cid)
{
//	ft_printf("close pipe n%ld %ld=%ld\n", cid-1, e->cmd[cid - 1].pipe[0],
//			  e->cmd[cid - 1].pipe[1]);
	close(e->cmd[cid - 1].pipe[0]);
	close(e->cmd[cid - 1].pipe[1]);
}

