/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_search_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 03:16:30 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/16 03:18:51 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	editor_search_print(t_env *e, char *line, char *search, int prompt)
{
	int		len;

	while (e->cur < e->line_len)
		move_cursor_right(e);
	while (e->cur)
		backdelete_input_char(e, 1);
	len = e->prompt_len;
	while (len)
	{
		e->cur++;
		e->line_len++;
		backdelete_input_char(e, 1);
		len--;
	}
	editor_search_print_prompt(e, search, prompt);
	if (e->line != e->line_save)
		free(e->line);
	e->line = ft_strdup(line);
	ft_putstr(e->line);
	e->line_len = ft_strlen(e->line);
	e->line_size = e->line_len;
	e->cur = e->line_len;
	editor_search_position_cursor(e, search);
}

void	editor_search_print_prompt(t_env *e, char *search, int prompt)
{
	char	*str;

	if (prompt)
	{
		str = ft_strdup("(reverse-i-search)`");
		str = ft_strdupcat(str, search);
		str = ft_strdupcat(str, "': ");
		gen_prompt(e, str);
		free(str);
	}
	else
		gen_prompt(e, NULL);
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
