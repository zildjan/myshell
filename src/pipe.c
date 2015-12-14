/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 21:54:46 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*
void	pipe_new(t_env *e)
{
	if (e->cid + 1 < e->nb_cmd && e->cmd[e->cid].out_t == R_PIPE)
	{
		e->cmd[e->cid].out_t = R_PIPED;
//		ft_printf("un pipe\n");
		pipe(e->cmd[e->cid].pipe);
	}
}

void	pipe_assign(t_env *e)
{
	if (e->cid + 1 < e->nb_cmd && e->nb_cmd > 1
		&& e->cmd[e->cid].out_t == R_PIPED)
	{
//		ft_printf("assign -> %ld vers %ld\n", e->cid, e->cid +1);
		close(e->cmd[e->cid].pipe[0]);
		dup2(e->cmd[e->cid].pipe[1], 1);
		close(e->cmd[e->cid].pipe[1]);
	}
	if (e->cid > 0 && e->cmd[e->cid].in_t == R_PIPE
		&& e->cmd[e->cid - 1].out_t == R_PIPED)
	{
//		ft_printf("assign <- %ld depuis %ld\n", e->cid -1, e->cid);
		close(e->cmd[e->cid - 1].pipe[1]);
		dup2(e->cmd[e->cid - 1].pipe[0], 0);
		close(e->cmd[e->cid - 1].pipe[0]);
	}
}

void	pipe_close(t_env *e)
{
	if (e->cid > 0 && e->cmd[e->cid].in_t == R_PIPE
		&& e->cmd[e->cid - 1].out_t == R_PIPED)
	{
//		ft_printf("close pipe\n");
		close(e->cmd[e->cid - 1].pipe[0]);
		close(e->cmd[e->cid - 1].pipe[1]);
	}
}

// */
