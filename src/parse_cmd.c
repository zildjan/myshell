/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/09 00:38:04 by pbourrie         ###   ########.fr       */
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
	parse_init(e, &p);
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
	if (!p.error && e->cmd[e->cid].arg)
		process_cmd(e);
	free_cmd(e);
}

int		parse_cmd_check_eol(t_env *e, t_parse *p)
{
	if (p->error)
		return (1);
	if (!e->line[++p->i])
	{
		if (p->ib && !p->quo && !p->escape)
		{
			parse_add_arg(e, p);
			if (e->line[p->i])
				return (0);
		}
		if (parse_cmd_is_end(p))
		{
			p->error = EP_EOF;
		}
		return (1);
	}
	return (0);
}

void	parse_cmd_loop_end(t_env *e, t_parse *p)
{
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
	e->cmd[0].name = ft_strsub(e->line, p->last_i, p->i - p->last_i);
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
	else if (p->sub > 0)
		return ('(');
	else if (!p->a_id && p->separ)
		return (p->separ);
	else
		return (0);
}
