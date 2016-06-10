/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/06/11 01:09:16 by pbourrie         ###   ########.fr       */
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
	char	*line_save;

	line_save = e->line;
	e->line = NULL;
	gen_prompt(e, "heredoc> ");
	get_heredoc_p2(e, eof);
	if (e->line)
		free(e->line);
	e->line = line_save;
}

void	get_heredoc_p2(t_env *e, char *eof)
{
	t_hdoc	*hdoc;
	t_hdoc	*prev;
	int		ret;
	int		total_len;

	total_len = 0;
	prev = NULL;
	free_heredoc(e, e->cid);
	print_prompt(e);
	ret = get_input_line(e, 0);
	while (!ft_strequ(e->line, eof) && ret != -1)
	{
		total_len += ft_strlen(e->line);
		if (total_len > MAX_LEN_HDOC)
			break ;
		hdoc = (t_hdoc*)ft_memalloc(sizeof(t_hdoc));
		hdoc->content = ft_strdup(e->line);
		if (prev)
			prev->next = hdoc;
		prev = hdoc;
		get_heredoc_p3(e, &ret, hdoc);
	}
}

void	get_heredoc_p3(t_env *e, int *ret, t_hdoc *hdoc)
{
	if (!e->cmd[e->cid].hdoc)
		e->cmd[e->cid].hdoc = hdoc;
	free(e->line);
	e->line = NULL;
	print_prompt(e);
	*ret = get_input_line(e, 0);
}
