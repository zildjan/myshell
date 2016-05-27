/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_alias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 21:19:43 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/27 23:44:06 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		parse_cmd_alias(t_env *e, t_parse *p)
{//return (0);
	t_alias	*alias;
	char	*line_save;
	char	*cmd;

	cmd = ft_strdup(p->buf);
	char *cmd_save;
	cmd_save = cmd;
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
	line_save = e->line;
	e->line = cmd;

//	ft_printf("->line='%s'\n", e->line);
	e->line = ft_strdupcat(e->line, line_save + p->i);

	free(line_save);
	p->ib = 0;
	if (p->i != p->line_len)
		p->i--;
	p->i -= ft_strlen(p->buf);
	ft_strclr(p->buf);
	p->quo = NONE;
	p->quoted = 1;
	p->line_len += ft_strlen(e->line);
//	ft_printf("-- line='%s' i=%d\n", e->line, p->i);
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
//	ft_printf("cmd='%s', word='%s'\n", *cmd, word);
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
//*/
