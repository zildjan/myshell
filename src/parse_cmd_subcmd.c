/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_subcmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 22:46:00 by pbourrie          #+#    #+#             */
/*   Updated: 2016/06/27 02:31:59 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	parse_cmd_subcmd(t_env *e, t_parse *p)
{
	if (!parse_cmd_subcmd_parse_line(e, p))
	{
		p->error = EP_EOF;
//		ft_printf("ICI buf='%s' sub=%d\n", p->buf, p->sub);
		return ;
	}
	p->quo = 0;
	p->bquo = 0;
	p->sub = 0;
	p->quoted = 1;
	parse_add_arg(e, p);
	e->cmd[e->cid].sub = 1;
//	printf("CELUICi ** ib=%d\n", p->ib);
//	ft_printf("[]subcmd='%s'\n", e->cmd[e->cid].arg[0]);
}

int		parse_cmd_subcmd_parse_line(t_env *e, t_parse *p)
{
	p->quo = NONE;
	p->bquo = 0;
	p->escape = 0;
	p->sub = 1;
	while (e->line[p->i++])
	{
//		ft_printf("-> '%c' \n", e->line[p->i]);
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
		if (p->quo)
			p->quo = NONE;
		else
			p->quo = SIMP;
	}
	else if (e->line[p->i] == '"' && (!p->quo || p->quo == DOUB)
			&& !p->escape)
	{
		if (p->quo)
			p->quo = NONE;
		else
			p->quo = DOUB;
	}
	else if (e->line[p->i] == '`' && p->quo != SIMP && !p->escape)
	{
		if (p->bquo)
			p->bquo = 0;
		else
			p->bquo = 1;
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
