/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_alias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 21:19:43 by pbourrie          #+#    #+#             */
/*   Updated: 2016/07/07 01:49:58 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		parse_cmd_alias(t_env *e, t_parse *p)
{
	char	*cmd_save;
	char	*cmd;

	cmd = ft_strdup(p->buf);
	cmd_save = cmd;
	p->doalias = 0;
	parse_cmd_alias_rec(e, p, &cmd);
	if (cmd == cmd_save)
	{
		free(cmd);
		return (0);
	}
	parse_cmd_alias_addtoline(e, p, cmd);
	if (p->i != p->line_len)
		p->i--;
	p->i -= ft_strlen(p->buf);
//	p->i++;
	p->aliased = p->i + ft_strlen(cmd);
	ft_strclr(p->buf);
	p->ib = 0;
	p->quo = NONE;
	p->line_len = ft_strlen(e->line);
	free(cmd);
	return (1);
}

void	parse_cmd_alias_addtoline(t_env *e, t_parse *p, char *cmd)
{
	char	*line_save;
	t_alias	*alias;

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
	free(line_save);
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
