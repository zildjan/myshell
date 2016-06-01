/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_substitution_parse_line.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 00:46:18 by pbourrie          #+#    #+#             */
/*   Updated: 2016/06/01 01:23:30 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		parse_cmd_substi_parse_line(t_env *e, t_parse *p, char *cmd)
{
	int		i;

	i = 0;
	p->quo = NONE;
	p->escape = 0;
	while (e->line[p->i])
	{
		parse_cmd_substi_parse_line_quotes(e, p);
		if (e->line[p->i] == '\\' && !p->escape &&
			(e->line[p->i + 1] == '\\'
			|| e->line[p->i + 1] == '$'
			|| e->line[p->i + 1] == '`'))
			p->escape = 2;
		else if (e->line[p->i] == '`' && !p->escape)
			return (1);
		else
			cmd[i++] = e->line[p->i];
		p->i++;
		if (p->escape)
			p->escape--;
	}
	return (0);
}

void	parse_cmd_substi_parse_line_quotes(t_env *e, t_parse *p)
{
	if (e->line[p->i] == '\'' && (!p->quo || p->quo == SIMP)
		&& !p->escape)
	{
		if (p->quo)
			p->quo = NONE;
		else
			p->quo = SIMP;
	}
	else if (e->line[p->i] == '"' && (!p->quo || p->quo == DOUB)
			&& !p->escape)
	{
		if (p->quo)
			p->quo = NONE;
		else
			p->quo = DOUB;
	}
}
