/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:26:46 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/13 18:33:50 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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

void	open_file_error(char *path, int type)
{
	char	ftype;
	int		mode;

	ftype = ft_get_file_type(path);
	mode = (ft_get_file_mode(path) / 100);
	if (ftype == -1)
		put_error(ERRNOENT, NULL, path, 2);
	else if (ftype == 'd')
		put_error(ERRISDIR, NULL, path, 2);
	else if ((type == R_OUT || type == R_OUTA) && mode != 2 && mode != 3
			&& mode != 6 && mode != 7)
		put_error(ERRACCES, NULL, path, 2);
	else if (type == R_IN && mode < 4)
		put_error(ERRACCES, NULL, path, 2);
	else
		put_error(0, NULL, path, 2);
}
