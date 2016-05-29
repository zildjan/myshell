/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_element_p1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:04:22 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/30 00:17:17 by pbourrie         ###   ########.fr       */
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
		return (parse_cmd_operator(e, p));
	return (1);
}

int		parse_cmd_operator(t_env *e, t_parse *p)
{
	if (e->line[p->i] == '&' && e->line[p->i + 1] == '&'
		&& !p->quo && !p->escape && p->ignore <= p->i)
	{
		p->i++;
		if (p->ib > 0)
			parse_add_arg(e, p);
		if (p->a_id == 0)
			p->error = EP_NULL_CMD;
		else
			parse_add_cmd(e, p, SEP_AND);
	}
	else if (e->line[p->i] == '|' && e->line[p->i + 1] == '|'
			&& !p->quo && !p->escape && p->ignore <= p->i)
	{
		p->i++;
		if (p->ib > 0)
			parse_add_arg(e, p);
		if (p->a_id == 0)
			p->error = EP_NULL_CMD;
		else
			parse_add_cmd(e, p, SEP_OR);
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
			parse_add_arg(e, p);
		if (p->a_id == 0)
			p->error = EP_NULL_CMD;
		else
			parse_add_cmd(e, p, SEP_PIPE);
	}
	else if (e->line[p->i] == ';' && !p->quo
			&& !p->escape && p->ignore <= p->i)
	{
		if (p->ib > 0)
			parse_add_arg(e, p);
		if (p->a_id == 0)
			p->error = EP_NULL_CMD;
		else
			parse_add_cmd(e, p, NONE);
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

int		parse_cmd_redirection(t_env *e, t_parse *p)
{
	if (((ft_isdigit(e->line[p->i]) && is_aspace(e->line[p->i - 1])
		&& (e->line[p->i + 1] == '<' || e->line[p->i + 1] == '>'))
		|| (e->line[p->i] == '<' || e->line[p->i] == '>'))
		&& !p->quo && !p->escape && p->ignore <= p->i)
	{
		if (p->ib > 0)
			parse_add_arg(e, p);
		p->redirec_fd = -1;
		if (ft_isdigit(e->line[p->i]))
			p->redirec_fd = e->line[p->i++] - 48;
		parse_get_redirec_type(e, p);
	}
	else
		return (parse_cmd_space_backslash(e, p));
	return (1);
}
