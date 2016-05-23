/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 00:34:22 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/23 18:00:26 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	lexer(t_env *e, t_parse *l, int end)
{
	l->quo = NONE;
	l->bquo = NONE;
	l->escape = 0;
	l->separ = 0;
	l->i = 0;
	l->ib = 0;
	l->line_len = ft_strlen(e->line);
	l->buf_len = l->line_len;
	l->buf = ft_strnew(l->buf_len);
	l->a_id = 0;
	l->end = end;
	if (end < 0)
		l->end = l->line_len;
	while (l->i < l->end && e->line[l->i])
	{
		lexer_quotes(e, l);
		l->i++;
		if (l->escape)
			l->escape--;
	}
	if (l->ib > 0 && end < 0)
		lexer_add_arg(l);
}

int		lexer_add_to_buf(t_env *e, t_parse *l)
{
	if (l->ib + 10 >= l->buf_len)
		realloc_parse_buffer(l, 10);
	if (e->line[l->i])
		l->buf[l->ib++] = e->line[l->i];
	return (1);
}

void	lexer_add_arg(t_parse *l)
{
	if (l->ib > 0)
		l->a_id++;
	ft_strclr(l->buf);
	l->ib = 0;
}
