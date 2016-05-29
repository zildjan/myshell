/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_alias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 21:19:43 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/30 00:07:16 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		parse_cmd_alias(t_env *e, t_parse *p)
{
	t_alias	*alias;
	char	*line_save;
	char	*cmd;

	cmd = ft_strdup(p->buf);
	char *cmd_save;
	cmd_save = cmd;
	p->doalias = 0;
	parse_cmd_alias_rec(e, p, &cmd);
	if (cmd == cmd_save)
	{
		free(cmd);
		return (0);
	}
	alias = e->alias;
	while (alias)
	{
		alias->used = 0;
		alias = alias->next;
	}
	if (cmd[ft_strlen(cmd) - 1] == ' ')
		p->doalias = 1;
	line_save = e->line;
	e->line = ft_strndup(e->line, p->i - p->ib);
	e->line = ft_strdupcat(e->line, cmd);
	e->line = ft_strdupcat(e->line, line_save + p->i);
	p->ib = 0;
	if (p->i != p->line_len)
		p->i--;
	p->i -= ft_strlen(p->buf);
	p->aliased = p->i + ft_strlen(cmd);
	ft_strclr(p->buf);
	p->quo = NONE;
	p->line_len = ft_strlen(e->line);
	free(cmd);
	free(line_save);
	return (1);
}


void	parse_cmd_alias_rec(t_env *e, t_parse *p, char **cmd)
{
	t_alias	*alias;
	char	*word;
	int		i;
	char	*tmp;

	i = 0;
	while ((*cmd)[i] && !is_aspace((*cmd)[i]))
		i++;
	word = ft_strndup(*cmd, i);
	alias = e->alias;
	while (alias)
	{
		if (ft_strequ(alias->key, word) && !alias->used)
		{
			tmp = ft_strdup(alias->val);
			tmp = ft_strdupcat(tmp, *cmd + i);
			free(*cmd);
			*cmd = tmp;
			alias->used = 1;
			parse_cmd_alias_rec(e, p, cmd);
			break ;
		}
		alias = alias->next;
	}
	free(word);
}
