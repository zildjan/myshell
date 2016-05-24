/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_alias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 21:19:43 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/24 23:06:46 by pbourrie         ###   ########.fr       */
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
			p->i = 0;
			p->quo = NONE;
			p->quoted = NONE;
			p->line_len += ft_strlen(alias->val);
			return (1);
		}
		alias = alias->next;
	}
	return (0);
}
