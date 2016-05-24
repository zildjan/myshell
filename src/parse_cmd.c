/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/24 21:12:33 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_cmd(t_env *e)
{
	t_parse	p;

	p.line_len = ft_strlen(e->line);
	if (p.line_len > MAX_LEN_LINE)
	{
		ft_putendl_fd("input line too long", 2);
		return ;
	}
	if (!p.line_len)
		return ;
	parse_cmd_init(e, &p);
	while (1)
	{
		if (parse_cmd_check_eol(e, &p))
			break ;
		parse_cmd_quotes(e, &p);
		if (p.escape)
			p.escape--;
	}
	parse_cmd_loop_end(e, &p);
	parse_cmd_put_error(&p);
	if (!p.error)
		process_cmd(e);
	free_cmd(e);
}

void	parse_cmd_init(t_env *e, t_parse *p)
{
	e->cid = 0;
	p->a_id = 0;
	e->nb_cmd = 1;
	p->quo = NONE;
	p->quoted = NONE;
	p->bquo = NONE;
	p->escape = 0;
	p->separ = 0;
	p->last_arg = NULL;
	p->redirec = NONE;
	p->error = 0;
	p->buf_len = p->line_len;
	p->buf = ft_strnew(p->buf_len);
	p->i = -1;
	p->ib = 0;
	e->cmd = (t_cmd*)ft_memalloc(sizeof(t_cmd) * (e->nb_cmd));
	e->cmd[0].redir = NULL;
	e->cmd[0].hdoc = NULL;
	e->cmd[0].condi = 0;
	e->cmd[0].fd_in = 0;
	e->cmd[0].fd_out = 1;
	e->cmd[0].fd_err = 2;
	p->ignore = 0;
}

int		parse_cmd_check_eol(t_env *e, t_parse *p)
{
	if (p->error)
		return (1);
	if (!e->line[++p->i])
	{
		if (p->ib && !p->quo && !p->escape)
			parse_add_arg(e, p);
		if (parse_cmd_is_end(p))
			p->error = EP_EOF;
		return (1);
	}
	return (0);
}

void	parse_cmd_loop_end(t_env *e, t_parse *p)
{
	if (p->escape && p->ib && !p->line_len)
		parse_add_arg(e, p);
	set_env_var(e, "_", p->last_arg);
	if (!p->error && p->a_id == 0)
	{
		if (!p->separ)
		{
			free_heredoc(e, e->cid);
			free_cmd_redirec(e, e->cid);
			e->nb_cmd--;
		}
		else
			p->error = EP_NULL_CMD;
	}
	if (!p->error && p->redirec)
		p->error = EP_MISS_REDIREC;
	free(p->buf);
	e->cid = 0;
}

int		parse_cmd_is_end(t_parse *p)
{
	if (p->quo == SIMP)
		return ('\'');
	else if (p->quo == DOUB)
		return ('"');
	else if (p->bquo)
		return ('`');
	else if (p->escape)
		return ('\\');
	else if (!p->a_id && p->separ)
		return (p->separ);
	else
		return (0);
}
