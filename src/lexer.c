/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 00:34:22 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/03 01:28:54 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	lexer(t_env *e, t_lex *l, int end)
{
	l->quo = NONE;
	l->escape = 0;
	l->i = 0;
	l->ib = 0;
	l->a_id = 0;
	l->cid = 0;
	l->end = end;
	while (l->i < l->end && e->line[l->i] && is_aspace(e->line[l->i]))
		l->i++;
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
		else if (((ft_isdigit(e->line[l->i]) && is_aspace(e->line[l->i - 1])
				&& (e->line[l->i + 1] == '<' || e->line[l->i + 1] == '>'))
				|| (e->line[l->i] == '<' || e->line[l->i] == '>'))
				&& !l->quo && !l->escape)
		{
			l->a_id++;
			if (ft_isdigit(e->line[l->i]))
				l->i++;
			if (e->line[l->i + 1] == '>' || e->line[l->i + 1] == '<')
				l->i++;
			while (is_aspace(e->line[l->i + 1]))
				l->i++;
		}
		else if (is_aspace(e->line[l->i]) && !l->quo && !l->escape)
			l->a_id++;
		else if (e->line[l->i] == '\\' && !l->escape
				&& ((!l->quo)
					|| (l->quo == DOUB && e->line[l->i + 1] == '"')
					|| (l->quo == DOUB && e->line[l->i + 1] == '$')
					|| (l->quo == DOUB && e->line[l->i + 1] == '\\')
					|| (l->quo == DOUB && !e->line[l->i + 1])))
			l->escape = 2;
//		else
//			l->ib++;
		l->i++;
		if (l->escape)
			l->escape--;
	}
}
