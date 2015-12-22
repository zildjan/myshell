/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/10 18:58:17 by pbourrie          #+#    #+#             */
/*   Updated: 2015/12/17 22:21:10 by pbourrie         ###   ########.fr       */
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
		else if (redir->type == R_FDOUT || redir->type == R_FDIN)
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
		redir = redir->next;
	}
	return (1);
}

int		getcurstdfd(t_env *e, int fd)
{
	if (fd == 0)
		return (e->cmd[e->cid].fd_in);
	else if (fd == 1)
		return (e->cmd[e->cid].fd_out);
	else if (fd == 2)
		return (e->cmd[e->cid].fd_err);
	else
		return (fd);
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
			if (redir->fd_to > -1)
				close(redir->fd_to);
		if (redir->type == R_PIPEIN && e->cmd[cid].piped)
			pipe_close(e, cid);
		else if (redir->type == R_HDOC)
		{
			if (redir->fd_to > 2)
			{
//				ft_printf("close %d\n", redir->fd_to);
				close(redir->fd_to);
			}
			redir->fd_to = -1;
		}
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
		open_file_error(redir->file, redir->type);
		return (0);
	}
	return (1);
}

void	open_file_error(char *path, int type)
{
	char	ftype;
	int		mode;

	ftype = ft_get_file_type(path);
	mode = (ft_get_file_mode(path) / 100);
	if (ftype == 'd')
		put_error(ERRISDIR, NULL, path, 2);
	else if ((type == R_OUT || type == R_OUTA) && mode != 2 && mode != 3
			 && mode != 6 && mode != 7)
		put_error(ERRACCES, NULL, path, 2);
	else if (type == R_IN && mode < 4)
		put_error(ERRACCES, NULL, path, 2);
	else
		put_error(0, NULL, path, 2);
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
