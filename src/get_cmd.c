/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 21:54:46 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	get_cmd(t_env *e)
{
	get_input_line(e);
	if (e->line == NULL)
		return ;
	parse_cmd(e);
	free(e->line);
	e->line = NULL;
}

void	get_cmd_end(t_env *e, char type)
{
//	ft_printf("GET END\n");
	if (e->line)
		free(e->line);
	e->line = NULL;
	if (type == SEP_PIPE)
		ft_putstr("pipe> ");
	else if (type == SEP_AND)
		ft_putstr("cmdand> ");
	else if (type == SEP_OR)
		ft_putstr("or> ");
	else if (type == '\'')
		ft_putstr("quote> ");
	else if (type == '"')
		ft_putstr("dquote> ");
	else
		ft_putstr("> ");
	get_input_line(e);
}

void	get_input_line(t_env *e)
{
	int		ret;

	ret = get_next_line(0, &e->line);
	if (ret == 0)
	{
		ft_printf("exit\n");
		builtin_exit(e);
	}
	if (!e->line)
		e->line = ft_strdup("");
}
