/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/21 23:27:17 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	get_cmd(t_env *e)
{
	get_input_line(e, 1);
	if (e->line == NULL)
		return ;

	t_parse		l;
	int			type;
	char		*line_start;
	int			ret;

	line_start = e->line;
	while (1)
	{
		lexer(e, &l, 0);
		type = parse_cmd_is_end(&l);
		if (!type)
		{
			if (e->line && e->line != line_start)
				free(e->line);
			e->line = line_start;
			break ;
		}
		ft_printf("SIII\n");
		ret = get_cmd_end(e, type);
		if (ret == -1)
			ft_putendl_fd("Syntax error: unexpected end of file", 2);
		if (ret)
		{
			if (line_start)
				free(line_start);
			if (e->line)
				free(e->line);
			return ;
		}
		line_start = ft_strdupcat(line_start, e->line);
	}
	
	parse_cmd(e);
	free(e->line);
	e->line = NULL;
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
		gen_prompt(e, "or> ");
	else if (type == '\'')
		gen_prompt(e, "quote> ");
	else if (type == '"')
		gen_prompt(e, "dquote> ");
	else if (type == '`')
		gen_prompt(e, "bquote> ");
	else
		gen_prompt(e, "> ");
	if (isatty(0))
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

	if (e->term)
		ret = get_term_line_input(e, eof_exit);
	else
	{
		ret = get_next_line(0, &e->line);
		if (ret == 0 && eof_exit)
		{
			if (isatty(0))
				ft_printf("exit\n");
			builtin_exit(e);
		}
		else if (ret == 0)
			ret = -1;
		if (!e->line)
			e->line = ft_strdup("");
	}
	return (ret);
}
