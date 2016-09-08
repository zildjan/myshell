/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_element_p1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:04:22 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/09 01:10:58 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		parse_cmd_quotes(t_env *e, t_parse *p)
{
	if (e->line[p->i] == '\'' && (!p->quo || p->quo == SIMP)
		&& !p->escape && p->ignore <= p->i)
	{
		p->quoted = SIMP;
		if (p->quo)
			parse_cmd_reset_quotes(e, p);
		else
			p->quo = SIMP;
	}
	else if (e->line[p->i] == '"' && (!p->quo || p->quo == DOUB)
			&& !p->escape && p->ignore <= p->i)
	{
		p->quoted = DOUB;
		if (p->quo)
			parse_cmd_reset_quotes(e, p);
		else
			p->quo = DOUB;
	}
	else if (e->line[p->i] == '`' && p->quo != SIMP
			&& !p->escape && p->ignore <= p->i)
		parse_cmd_substitution(e, p);
	else
		return (parse_cmd_operator_parenthesis(e, p));
	return (1);
}

int		parse_cmd_operator_parenthesis(t_env *e, t_parse *p)
{
	if (e->line[p->i] == '(' && !p->quo && !p->escape
		&& p->ignore <= p->i)
	{
		if (p->ib > 0)
			if (!parse_add_arg(e, p))
				return (1);
		if (p->a_id)
		{
			p->error = EP_SYNTAX;
			return (1);
		}
		parse_cmd_subcmd(e, p);
	}
	else if (e->line[p->i] == '&' && e->line[p->i + 1] == '&'
		&& !p->quo && !p->escape && p->ignore <= p->i)
	{
		if (parse_operators(e, p, SEP_AND, 1))
			return (1);
	}
	else
		return (parse_cmd_operator_ampersand(e, p));
	return (1);
}

int		parse_cmd_operator_ampersand(t_env *e, t_parse *p)
{
	if (e->line[p->i] == '|' && e->line[p->i + 1] == '|'
			&& !p->quo && !p->escape && p->ignore <= p->i)
	{
		if (parse_operators(e, p, SEP_OR, 1))
			return (1);
	}
	else if (e->line[p->i] == '&' && !p->quo
			&& !p->escape && p->ignore <= p->i)
	{
		e->background_cmd = 1;
		if (parse_operators(e, p, NONE, 0))
			return (1);
	}
	else
		return (parse_cmd_pipe_comma(e, p));
	return (1);
}

int		parse_cmd_pipe_comma(t_env *e, t_parse *p)
{
	if (e->line[p->i] == '|' && !p->quo
		&& !p->escape && p->ignore <= p->i)
	{
		if (p->ib > 0)
			if (!parse_add_arg(e, p))
				return (1);
		if (p->a_id == 0)
			p->error = EP_NULL_CMD;
		else
			parse_add_cmd(e, p, SEP_PIPE);
	}
	else if (e->line[p->i] == ';' && !p->quo
			&& !p->escape && p->ignore <= p->i)
	{
		if (parse_operators(e, p, NONE, 0))
			return (1);
	}
	else
		return (parse_cmd_expansion(e, p));
	return (1);
}

int		parse_cmd_expansion(t_env *e, t_parse *p)
{
	if (e->line[p->i] == '$' && p->quo != SIMP
		&& !p->escape && p->ignore <= p->i)
	{
		parse_var_expansion(e, p);
	}
	else if (e->line[p->i] == '~' && !p->quo && !p->ib
			&& !p->escape && p->ignore <= p->i)
	{
		parse_tilde_expansion(e, p);
	}
	else
		return (parse_cmd_redirection(e, p));
	return (1);
}
