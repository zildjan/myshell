/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/06 20:28:47 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	get_cmd(t_env *e)
{
	get_input_line(e, 1);
	if (e->line == NULL)
		return ;
	parse_cmd(e);
	free(e->line);
	e->line = NULL;
}

int		get_cmd_end(t_env *e, char type)
{
	int		ret;

	if (e->line)
		free(e->line);
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
	else
		gen_prompt(e, "> ");
	print_prompt(e);
	ret = get_input_line(e, 0);
	if (ret == -1 && type)
		return (EP_EOF);
	if (ret == -2)
		return (100);
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
