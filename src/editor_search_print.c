/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_search_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 03:16:30 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/24 17:53:00 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	editor_search_print(t_env *e, char *line, char *search, char *prompt)
{
	int		len;

	while (e->cur > 0)
		move_cursor_left(e);
	len = e->prompt_len;
	while (len)
	{
		e->cur++;
		move_cursor_left(e);
		len--;
	}
	tputs(tgetstr("dm", NULL), 0, ft_outc);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	tputs(tgetstr("ed", NULL), 0, ft_outc);
	editor_search_print_prompt(e, search, prompt);
	if (e->line != e->line_save)
		free(e->line);
	e->line = ft_strdup(line);
	e->line_len = ft_strlen(e->line);
	e->line_size = e->line_len;
	e->cur = e->line_len;
	put_line(e, 0);
	editor_search_position_cursor(e, search);
}

void	editor_search_print_prompt(t_env *e, char *search, char *prompt)
{
	char	*str;

	if (!prompt)
	{
		str = ft_strdup("(reverse-i-search)`");
		str = ft_strdupcat(str, search);
		str = ft_strdupcat(str, "': ");
		gen_prompt(e, str);
		free(str);
	}
	else
		gen_prompt(e, prompt);
	print_prompt(e);
}

void	editor_search_position_cursor(t_env *e, char *search)
{
	int		i;
	int		len;

	i = e->line_len;
	len = ft_strlen(search);
	while (--i >= 0 && len)
	{
		if (ft_strnequ(e->line + i, search, len))
			break ;
	}
	while (e->cur > i && i >= 0 && len)
		move_cursor_left(e);
}
