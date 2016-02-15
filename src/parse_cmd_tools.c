/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 17:09:42 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/12 22:55:13 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		is_aspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

void	parse_cmd_cleanline(t_env *e)
{
	int		start;
	int		len;
	char	*temp;

	start = 0;
	while (e->line[start] && is_aspace(e->line[start]))
		start++;
	len = ft_strlen(e->line) - 1;
	while (len > 0 && is_aspace(e->line[len]))
		len--;
	temp = ft_strsub(e->line, start, len - start + 1);
	free(e->line);
	e->line = temp;
}

void	realloc_parse_buffer(t_parse *p, int add)
{
	int		old;
	int		new;

	old = sizeof(char) * p->buf_len;
	new = sizeof(char) * (p->buf_len + add);
	p->buf = ft_memrealloc(p->buf, old, new);
	p->buf_len += add;
}

char	*dup_arg(char *buf)
{
	if (!buf)
		return (NULL);
	if (ft_strlen(buf) > MAX_LEN_ARG)
		return (ft_strndup(buf, MAX_LEN_ARG));
	return (ft_strdup(buf));
}

void	parse_cmd_put_error(t_parse *p)
{
	if (p->error)
	{
		if (p->error == EP_NULL_CMD)
			ft_putendl_fd("Invalid null command.", 2);
		else if (p->error == EP_AMB_OUT)
			ft_putendl_fd("Ambiguous output redirect.", 2);
		else if (p->error == EP_AMB_IN)
			ft_putendl_fd("Ambiguous input redirect.", 2);
		else if (p->error == EP_MISS_REDIREC)
			ft_putendl_fd("Missing name for redirect.", 2);
		else if (p->error == EP_BAD_FD)
			ft_putendl_fd("Bad file descriptor.", 2);
		else if (p->error == EP_SYNTAX)
			ft_putendl_fd("Syntax error.", 2);
		else if (p->error == EP_EOF)
			ft_putendl_fd("Syntax error: unexpected end of file", 2);
	}
}
