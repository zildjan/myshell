/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_subcmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 22:46:00 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/18 03:31:29 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_cmd_subcmd(t_env *e, t_parse *p)
{
	p->quo = NONE;
	p->bquo = 0;
	p->escape = 0;
	p->sub = 1;
	if (!parse_cmd_subcmd_parse_line(e, p))
	{
		p->error = EP_EOF;
		return ;
	}
	p->quo = 0;
	p->bquo = 0;
	p->sub = 0;
	p->quoted = 1;
	parse_add_arg(e, p);
	e->cmd[e->cid].sub = 1;
}

int		parse_cmd_subcmd_parse_line(t_env *e, t_parse *p)
{
	while (e->line[p->i++])
	{
		parse_cmd_subcmd_parse_line_quotes(e, p);
		if (e->line[p->i] == '\\' && !p->escape &&
			(e->line[p->i + 1] == '\\'
			|| e->line[p->i + 1] == '$'
			|| e->line[p->i + 1] == '`'))
			p->escape = 2;
		else if (e->line[p->i] == ')' && !p->escape && !p->quo
				&& !p->bquo && !p->sub)
			return (1);
		else
		{
			if (p->ib + 10 >= p->buf_len)
				realloc_parse_buffer(p, 10);
			if (e->line[p->i])
				p->buf[p->ib++] = e->line[p->i];
		}
		if (p->escape)
			p->escape--;
	}
	return (0);
}

void	parse_cmd_subcmd_parse_line_quotes(t_env *e, t_parse *p)
{
	if (e->line[p->i] == '\'' && (!p->quo || p->quo == SIMP)
		&& !p->escape)
	{
		p->quo = (p->quo) ? NONE : SIMP;
	}
	else if (e->line[p->i] == '"' && (!p->quo || p->quo == DOUB)
			&& !p->escape)
	{
		p->quo = (p->quo) ? NONE : DOUB;
	}
	else if (e->line[p->i] == '`' && p->quo != SIMP && !p->escape)
	{
		p->bquo = (p->bquo) ? 0 : 1;
	}
	else if (e->line[p->i] == '(' && !p->quo && !p->bquo && !p->escape)
	{
		p->sub++;
	}
	else if (e->line[p->i] == ')' && !p->quo && !p->bquo && !p->escape)
	{
		p->sub--;
	}
}
