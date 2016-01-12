/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_element_p2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:05:18 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/12 17:05:39 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		parse_cmd_space_backslash(t_env *e, t_parse *p)
{
	if (is_aspace(e->line[p->i]) && !p->quo && !p->escape)
	{
		if (p->ib > 0)
			parse_add_arg(e, p);
	}
	else if (e->line[p->i] == '\\' && !p->escape
			&& ((!p->quo)
				|| (p->quo == DOUB && e->line[p->i + 1] == '"')
				|| (p->quo == DOUB && !e->line[p->i + 1])
				|| (e->line[p->i + 1] == '\\')))
	{
		p->escape = 2;
	}
	else
		return (parse_cmd_add_to_buf(e, p));
	return (1);
}

int		parse_cmd_add_to_buf(t_env *e, t_parse *p)
{
	if (p->ib + 10 >= p->buf_len)
		realloc_parse_buffer(p, 10);
	if (e->line[p->i])
		p->buf[p->ib++] = e->line[p->i];
	return (1);
}
