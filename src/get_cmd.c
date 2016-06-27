/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/06/27 22:47:24 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	get_cmd(t_env *e)
{
	t_parse	lex;

	get_input_line(e, 1);
	if (e->line == NULL)
		return ;
	lex = get_cmd_is_ended(e);
	if (e->line == NULL)
		return ;
//	ft_printf("line='%s'\n", e->line);
	if (e->term && !e->fd_in)
		history_save_ent(e, e->line);
	if (!lex.error)
	{
//		ft_printf("PARSING\n");
		parse_cmd(e);
	}
	else
	{
		parse_cmd_put_error(&lex);
		e->status = 258;
	}
	free(e->line);
	e->line = NULL;
}

t_parse	get_cmd_is_ended(t_env *e)
{
	t_parse		l;
	int			type;
	char		*line_start;

	line_start = e->line;
	while (1)
	{
		lexer(e, &l, -1);
		free(l.buf);
		type = parse_cmd_is_end(&l);
		if (!type)
		{
			if (e->line && e->line != line_start)
				free(e->line);
			e->line = line_start;
			break ;
		}
		if (get_cmd_get_end(e, &l, &line_start, type))
			return (l);
	}
	return (l);
}

int		get_cmd_get_end(t_env *e, t_parse *l, char **line_start, int type)
{
	int		ret;

	if (l->buf_len && l->escape)
		e->line[ft_strlen(e->line) - 1] = 0;
	else if (l->quo)
		e->line = ft_strdupcat(e->line, "\n");
	*line_start = e->line;
	ret = get_cmd_end(e, type);
	*line_start = ft_strdupcat(*line_start, e->line);
	free(e->line);
	e->line = *line_start;
	if (ret == -1)
		ft_putendl_fd("Syntax error: unexpected end of file", 2);
	if (ret)
	{
		if (e->line)
			free(e->line);
		e->line = NULL;
		return (1);
	}
	return (0);
}

int		get_cmd_end(t_env *e, char type)
{
	int		ret;

	e->line = NULL;
	if (type == SEP_PIPE)
		gen_prompt(e, "pipe> ");
	else if (type == SEP_AND)
		gen_prompt(e, "cmdand> ");
	else if (type == SEP_OR)
		gen_prompt(e, "cmdor> ");
	else if (type == '\'')
		gen_prompt(e, "quote> ");
	else if (type == '"')
		gen_prompt(e, "dquote> ");
	else if (type == '`')
		gen_prompt(e, "bquote> ");
	else if (type == '(')
		gen_prompt(e, "subsh> ");
	else
		gen_prompt(e, "> ");
	if (isatty(e->fd_in))
		print_prompt(e);
	ret = get_input_line(e, 0);
	if (ret == -1 && type)
		return (-1);
	if (ret == -2)
		return (-2);
	return (0);
}

int		get_input_line(t_env *e, int eof_exit)
{
	int		ret;

	if (e->term && !e->fd_in)
		ret = get_term_line_input(e, eof_exit);
	else
	{
		ret = get_next_line(e->fd_in, &e->line);
		if (ret == 0 && eof_exit)
		{
			if (isatty(e->fd_in))
				ft_printf("exit\n");
			if (e->fd_in)
				e->fd_in = -1;
			else
				builtin_exit(e);
		}
		else if (ret == 0)
			ret = -1;
		if (!e->line)
			e->line = ft_strdup("");
	}
	return (ret);
}
