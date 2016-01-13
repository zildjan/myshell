/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/10 18:58:17 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/13 18:42:15 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		redirec_open_all(t_env *e)
{
	t_redir	*redir;

	redir = e->cmd[e->cid].redir;
	while (redir)
	{
		if (!redirec_open_p1(e, redir))
		{
			return (0);
		}
		redir = redir->next;
	}
	return (1);
}

int		redirec_open_p1(t_env *e, t_redir *redir)
{
	if (redir->type == R_OUT || redir->type == R_OUTA
		|| redir->type == R_IN)
	{
		if (!redirec_open_files(redir))
			return (0);
		if (redir->type == R_IN)
			e->cmd[e->cid].piped = 0;
	}
	else if (redir->type == R_PIPEOUT)
	{
		if (!pipe_new(e, redir))
			return (0);
		redir->fd_to = e->cmd[e->cid].pipe[1];
	}
	else if (redir->type == R_PIPEIN)
	{
		e->cmd[e->cid].piped = 1;
		redir->fd_to = e->cmd[e->cid - 1].pipe[0];
	}
	else
		return (redirec_open_p2(e, redir));
	return (1);
}

int		redirec_open_p2(t_env *e, t_redir *redir)
{
	if (redir->type == R_FDOUT || redir->type == R_FDIN)
	{
		if (!redirec_open_dupfd(redir))
			return (0);
	}
	else if (redir->type == R_HDOC)
	{
		if (!read_heredoc(e, redir))
			return (0);
		e->cmd[e->cid].piped = 0;
	}
	if (redir->fd == 0)
		e->cmd[e->cid].fd_in = getcurstdfd(e, redir->fd_to);
	else if (redir->fd == 1)
		e->cmd[e->cid].fd_out = getcurstdfd(e, redir->fd_to);
	else if (redir->fd == 2)
		e->cmd[e->cid].fd_err = getcurstdfd(e, redir->fd_to);
	return (1);
}

void	redirec_assign(t_env *e)
{
	t_redir	*redir;

	redir = e->cmd[e->cid].redir;
	while (redir)
	{
		if (redir->type == R_OUT || redir->type == R_OUTA
			|| redir->type == R_IN)
			dup2(redir->fd_to, redir->fd);
		else if (redir->type == R_PIPEIN || redir->type == R_PIPEOUT)
			pipe_assign(e, redir);
		else if (redir->type == R_FDOUT || redir->type == R_FDIN)
			redirec_assign_dupfd(redir);
		else if (redir->type == R_HDOC)
			heredoc_assign(e, redir);
		redir = redir->next;
	}
}

void	redirec_close(t_env *e, int cid)
{
	t_redir	*redir;

	redir = e->cmd[cid].redir;
	while (redir)
	{
		if (redir->type == R_OUT || redir->type == R_OUTA
			|| redir->type == R_IN)
		{
			if (redir->fd_to > -1)
			{
				close(redir->fd_to);
				redir->fd_to = -1;
			}
		}
		if (redir->type == R_PIPEIN && e->cmd[cid].piped)
			pipe_close(e, cid);
		else if (redir->type == R_HDOC)
		{
			if (redir->fd_to > 2)
				close(redir->fd_to);
			redir->fd_to = -1;
		}
		redir = redir->next;
	}
}
