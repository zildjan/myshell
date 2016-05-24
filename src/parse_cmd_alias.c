/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_alias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 21:19:43 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/25 00:20:15 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		parse_cmd_alias(t_env *e, t_parse *p)
{
	t_alias	*alias;
	char	*line_save;

	alias = e->alias;
	while (alias)
	{
		if (ft_strequ(alias->key, p->buf))
		{
			ft_strclr(p->buf);
			line_save = e->line;
			e->line = ft_strdup(alias->val);
			e->line = ft_strdupcat(e->line, line_save + p->ib);
			free(line_save);
			p->ib = 0;
			p->i = -1;
			p->quo = NONE;
			p->quoted = -1;
			p->line_len += ft_strlen(e->line);
//			ft_printf("'%s' i=%d len=%d\n", e->line, p->i, p->line_len);
			return (1);
		}
		alias = alias->next;
	}
	return (0);
}
