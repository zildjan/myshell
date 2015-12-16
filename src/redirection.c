/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/10 18:58:17 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 22:15:38 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		redirec_open(t_env *e)
{
	t_redir	*redir;

	redir = e->cmd[e->cid].redir;
	while (redir)
	{
//		ft_printf("%s %ld %ld>%s\n", e->carg[0], redir->type, redir->fd, redir->file);
		if (redir->type == R_OUT || redir->type == R_OUTA
			|| redir->type == R_IN)
		{
			if (!redirec_open_files(redir))
				return (0);
		}
		else if (redir->type == R_PIPEOUT)
		{
			if (!pipe_new(e, redir))
				return (0);
		}
		else if (redir->type == R_FDOUT || redir->type == R_FDIN)
		{
			if (!redirec_open_dupfd(redir))
				return (0);
		}
		redir = redir->next;
	}
	return (1);
}

void	redirec_assign(t_env *e)
{
	t_redir	*redir;
//	return ;
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
		redir = redir->next;
	}
}

void	redirec_close(t_env *e)
{
	t_redir	*redir;

	redir = e->cmd[e->cid].redir;
	while (redir)
	{
		if (redir->type == R_OUT || redir->type == R_OUTA
			|| redir->type == R_IN)
			if (redir->fd_to > -1)
				close(redir->fd_to);
		if (redir->type == R_PIPEIN)
			pipe_close(e);
		redir = redir->next;
	}
}

int		redirec_open_files(t_redir *redir)
{
	if (redir->type == R_OUT)
		redir->fd_to = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == R_IN)
		redir->fd_to = open(redir->file, O_RDONLY);
	else
		redir->fd_to = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd_to == -1)
	{
		ft_putstr_fd("Error : can't open file : ", 2);
		ft_putendl_fd(redir->file, 2);
		return (0);
	}
	return (1);
}

int		redirec_open_dupfd(t_redir *redir)
{
	if (ft_isdigit(redir->file[0]))
		redir->fd_to = redir->file[0] - 48;
	else
		redir->fd_to = -2;
	if (redir->fd_to > 2)
	{
		redir->fd_to = -1;
		ft_putstr_fd("Error : Bad file descriptor : ", 2);
		ft_putendl_fd(redir->file, 2);
		return (0);
	}
	return (1);
}

void	redirec_assign_dupfd(t_redir *redir)
{
	if (redir->fd_to > -1)
		dup2(redir->fd_to, redir->fd);
	else if (redir->fd_to == -2)
		close(redir->fd);
}
