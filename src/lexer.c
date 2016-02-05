/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 00:34:22 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/05 01:22:50 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	lexer(t_env *e, t_parse *l, int end)
{
	l->quo = NONE;
	l->escape = 0;
	l->i = 0;
	l->ib = 0;
	l->buf_len = e->line_len;
	l->buf = ft_strnew(l->buf_len);
	l->a_id = 0;
	l->end = end;
	l->buf_begin = 0;
	while (l->i < l->end && e->line[l->i])
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
		else if (e->line[l->i] == '&' && e->line[l->i + 1] == '&'
				 && !l->quo && !l->escape)
		{
			l->i++;
			l->a_id = 0;
		}
		else if (e->line[l->i] == '|' && e->line[l->i + 1] == '|'
				 && !l->quo && !l->escape)
		{
			l->i++;
			l->a_id = 0;
		}
		else if (e->line[l->i] == '|' && !l->quo && !l->escape)
			l->a_id = 0;
		else if (e->line[l->i] == ';' && !l->quo && !l->escape)
			l->a_id = 0;
		else if (e->line[l->i] == '~' && !l->quo && !l->ib
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
		else if (is_aspace(e->line[l->i]) && !l->quo && !l->escape)
			lexer_add_arg(l);
		else if (e->line[l->i] == '\\' && !l->escape
				 && ((!l->quo)
					 || (l->quo == DOUB && e->line[l->i + 1] == '"')
					 || (l->quo == DOUB && e->line[l->i + 1] == '$')
					 || (l->quo == DOUB && e->line[l->i + 1] == '\\')
					 || (l->quo == DOUB && !e->line[l->i + 1])))
			l->escape = 2;
		else
		{
			if (l->ib + 10 >= l->buf_len)
				realloc_parse_buffer(l, 10);
			if (e->line[l->i])
				l->buf[l->ib++] = e->line[l->i];
		}
		l->i++;
		if (l->escape)
			l->escape--;
	}
}

void	lexer_add_arg(t_parse *l)
{
	if (l->ib > 0)
		l->a_id++;
	ft_strclr(l->buf);
	l->ib = 0;
	l->buf_begin = l->i;
}
