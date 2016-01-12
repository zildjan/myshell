/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_add_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:08:16 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/12 17:09:22 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		parse_add_redirec(t_env *e, t_parse *p)
{
	if (!p->ib)
		return (p->error = EP_MISS_REDIREC);
	if (p->redirec_fd < 0)
	{
		p->redirec_fd = 0;
		if (p->redirec == R_OUTA || p->redirec == R_OUT)
			p->redirec_fd = 1;
	}
	if (p->buf[0] == '&')
	{
		if (!ft_isdigit(p->buf[1]) && p->buf[1] != '-')
			p->error = EP_BAD_FD;
		else if (p->buf[2])
			p->error = EP_SYNTAX;
		if (p->redirec == R_OUT)
			new_redirec(e, p->buf + 1, R_FDOUT, p->redirec_fd);
		else
			new_redirec(e, p->buf + 1, R_FDIN, p->redirec_fd);
	}
	else
		new_redirec(e, p->buf, p->redirec, p->redirec_fd);
	parse_add_redirec_p2(p);
	return (0);
}

void	parse_add_redirec_p2(t_parse *p)
{
	ft_strclr(p->buf);
	p->ib = 0;
	p->quo = NONE;
	p->redirec = NONE;
	p->redirec_fd = -1;
}

void	parse_get_redirec_type(t_env *e, t_parse *p)
{
	if (p->redirec)
		p->error = EP_MISS_REDIREC;
	if (e->line[p->i] == '>' && e->line[p->i + 1] != '>')
		p->redirec = R_OUT;
	else if (e->line[p->i] == '>' && e->line[p->i + 1] == '>')
	{
		p->redirec = R_OUTA;
		p->i++;
		if (e->line[p->i + 1] == '&')
			p->error = EP_SYNTAX;
	}
	else if (e->line[p->i] == '<' && e->line[p->i + 1] != '<')
		p->redirec = R_IN;
	else if (e->line[p->i] == '<' && e->line[p->i + 1] == '<')
	{
		p->redirec = R_HDOC;
		p->i++;
		if (e->line[p->i + 1] == '&')
			p->error = EP_SYNTAX;
	}
	while (is_aspace(e->line[p->i + 1]))
		p->i++;
}

void	new_redirec(t_env *e, char *file, int type, int fd)
{
	t_redir		*new;
	t_redir		*tmp;

	new = (t_redir*)ft_memalloc(sizeof(t_redir));
	new->file = dup_arg(file);
	new->type = type;
	new->fd = fd;
	new->fd_to = -1;
	if (file == NULL)
	{
		new->next = e->cmd[e->cid].redir;
		e->cmd[e->cid].redir = new;
		return ;
	}
	tmp = e->cmd[e->cid].redir;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		e->cmd[e->cid].redir = new;
	if (type == R_HDOC)
		get_heredoc(e, file);
}
