/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/12/17 21:48:35 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		read_heredoc(t_env *e, t_redir *redir)
{
	t_hdoc	*tmp;
	int		len;

	if ((pipe(e->cmd[e->cid].hdoc_pipe) == -1))
	{
		ft_putstr_fd("Error : can't create pipe ", 2);
		redir->type = R_PIPENOT;
		return (0);
	}
	redir->fd_to = e->cmd[e->cid].hdoc_pipe[0];
	tmp = e->cmd[e->cid].hdoc;
	while (tmp)
	{
		len = ft_strlen(tmp->content);
		write(e->cmd[e->cid].hdoc_pipe[1], tmp->content, len);
		write(e->cmd[e->cid].hdoc_pipe[1], "\n", 1);
		tmp = tmp->next;
	}
	close(e->cmd[e->cid].hdoc_pipe[1]);
	return (1);
}

void	heredoc_assign(t_env *e, t_redir *redir)
{
	close(e->cmd[e->cid].hdoc_pipe[1]);
	dup2(redir->fd_to, redir->fd);
	close(e->cmd[e->cid].hdoc_pipe[0]);
}

void	get_heredoc(t_env *e, char *eof)
{
	char	*line;
	t_hdoc	*hdoc;
	t_hdoc	*prev;
	int		ret;
	int		total_len;

	total_len = 0;
	prev = NULL;
	free_heredoc(e, e->cid);
	ft_putstr("heredoc> ");
	ret = get_next_line(0, &line);
	while (!ft_strequ(line, eof) && ret != 0)
	{
		total_len += ft_strlen(line);
		if (total_len > MAX_LEN_HDOC)
			break ;
		hdoc = (t_hdoc*)ft_memalloc(sizeof(t_hdoc));
		hdoc->content = ft_strdup(line);
		if (prev)
			prev->next = hdoc;
		prev = hdoc;
		if (!e->cmd[e->cid].hdoc)
			e->cmd[e->cid].hdoc = hdoc;
		free(line);
		line = NULL;
		ft_putstr("heredoc> ");
		ret = get_next_line(0, &line);
	}
	if (line)
		free(line);
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
