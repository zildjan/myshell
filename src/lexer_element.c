/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 00:29:40 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/30 00:19:39 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		lexer_quotes(t_env *e, t_parse *l)
{
	if (e->line[l->i] == '\'' && (!l->quo || l->quo == SIMP)
		&& !l->escape)
	{
		if (l->quo)
			l->quo = NONE;
		else
			l->quo = SIMP;
	}
	else if (e->line[l->i] == '"' && (!l->quo || l->quo == DOUB)
			&& !l->escape)
	{
		if (l->quo)
			l->quo = NONE;
		else
			l->quo = DOUB;
	}
	else if (e->line[l->i] == '`' && l->quo != SIMP && !l->escape)
	{
		if (l->bquo)
			l->bquo = NONE;
		else
		{
			l->bquo = 1;
			l->a_id = 0;
		}
	}
	else
		return (lexer_operator_delim(e, l));
	return (1);
}

int		lexer_operator_delim(t_env *e, t_parse *l)
{
	if (e->line[l->i] == '&' && e->line[l->i + 1] == '&'
		&& !l->quo && !l->escape)
	{
		l->i++;
		l->a_id = 0;
		l->separ = SEP_AND;
	}
	else if (e->line[l->i] == '|' && e->line[l->i + 1] == '|'
			&& !l->quo && !l->escape)
	{
		l->i++;
		l->a_id = 0;
		l->separ = SEP_OR;
	}
	else if (e->line[l->i] == '|' && !l->quo && !l->escape)
	{
		l->a_id = 0;
		l->separ = SEP_PIPE;
	}
	else if (e->line[l->i] == ';' && !l->quo && !l->escape)
	{
		l->a_id = 0;
		l->separ = NONE;
	}
	else
		return (lexer_exp_redir(e, l));
	return (1);
}

int		lexer_exp_redir(t_env *e, t_parse *l)
{
	if (e->line[l->i] == '~' && !l->quo && !l->ib
		&& !l->escape)
	{
		parse_tilde_expansion(e, l);
	}
	else if (((ft_isdigit(e->line[l->i]) && is_aspace(e->line[l->i - 1])
			&& (e->line[l->i + 1] == '<' || e->line[l->i + 1] == '>'))
			|| (e->line[l->i] == '<' || e->line[l->i] == '>'))
			&& !l->quo && !l->escape)
	{
		lexer_add_arg(l);
		if (ft_isdigit(e->line[l->i]))
			l->i++;
		if (e->line[l->i + 1] == '>' || e->line[l->i + 1] == '<')
			l->i++;
		if (e->line[l->i + 1] == '&')
			l->i++;
		while (is_aspace(e->line[l->i + 1]))
			l->i++;
	}
	else
		return (lexer_space_escape(e, l));
	return (1);
}

int		lexer_space_escape(t_env *e, t_parse *l)
{
	if (is_aspace(e->line[l->i]) && !l->quo && !l->escape)
	{
		lexer_add_arg(l);
	}
	else if (e->line[l->i] == '\\' && !l->escape
			&& ((!l->quo)
				|| (l->quo == DOUB && e->line[l->i + 1] == '"')
				|| (l->quo == DOUB && e->line[l->i + 1] == '$')
				|| (l->quo == DOUB && e->line[l->i + 1] == '\\')
				|| (l->quo == DOUB && !e->line[l->i + 1])))
	{
		l->escape = 2;
	}
	else
		return (lexer_add_to_buf(e, l));
	return (1);
}
