/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_element_p2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:05:18 by pbourrie          #+#    #+#             */
/*   Updated: 2016/07/09 02:00:48 by pbourrie         ###   ########.fr       */
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
	else if (e->line[p->i] == '\\' && !p->escape && p->ignore <= p->i
			&& ((!p->quo)
				|| (p->quo == DOUB && e->line[p->i + 1] == '"')
				|| (p->quo == DOUB && e->line[p->i + 1] == '$')
				|| (p->quo == DOUB && e->line[p->i + 1] == '\\')
				|| (p->quo == DOUB && !e->line[p->i + 1])))
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

void	parse_cmd_reset_quotes(t_env *e, t_parse *p)
{
	if ((is_aspace(e->line[p->i + 1]) || !e->line[p->i + 1]) && !p->ib)
		parse_add_arg(e, p);
	p->quo = NONE;
}

int		parse_operators(t_env *e, t_parse *p, int separ, char doub)
{
//	ft_printf("a_id=%d buf='%s' l='%s' ", p->a_id, p->buf, e->line+p->i);
//	ft_printf("line='%s'\n", e->line);
	if (p->ib > 0)
		if (!parse_add_arg(e, p))
			return (1);

	if (doub)
		p->i++;
	if (p->a_id == 0)
		p->error = EP_NULL_CMD;
//		p->error = EP_AMB_IN;
	else
	{
		if (p->redirec)
			p->error = EP_MISS_REDIREC;
		if (!p->error)
			process_cmd(e);
		else
			return (1);
		free_cmd(e);
		parse_init_cmd(e, p);
		p->quoted = NONE;
		p->doalias = 0;
		p->separ = separ;
		if (p->last_arg)
		{
			set_env_var(e, "_", p->last_arg);
			free(p->last_arg);
			p->last_arg = NULL;
		}
		parse_add_cmd_sep(e, p, p->separ);
	}
//	ft_printf("->a_id=%d buf='%s' l='%s'\n", p->a_id, p->buf, e->line+p->i);
	return (0);
}
