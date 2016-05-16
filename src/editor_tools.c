/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:47:23 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/16 00:48:31 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	realloc_input_line(t_env *e)
{
	char	refresh;

	if (e->line_len + 10 >= e->line_size)
	{
		refresh = 0;
		if (e->line_save == e->line)
			refresh = 1;
		e->line = ft_memrealloc(e->line, e->line_size, e->line_size + 10);
		if (refresh)
			e->line_save = e->line;
		e->line_size += 10;
	}
}

int		is_end_of_line(t_env *e, int cur)
{
	if (!(get_cur_pos(e, cur) % e->ws_col))
	{
		return (1);
	}
	return (0);
}

int		get_cur_pos(t_env *e, int cur)
{
	int		pos;
	int		i;
	int		tmp;

	pos = e->prompt_len;
	i = -1;
	while (++i < cur && i < e->line_len)
	{
		if (e->line[i] == '\t')
		{
			tmp = pos % e->ws_col;
			tmp = tmp % e->t.tab_len;
			pos += e->t.tab_len - tmp;
		}
		else
			pos++;
	}

//	ft_printf("\npos=%ld\n", pos);

/*
	int save;

		ft_putchar('\n');
		close_line_edition(e);
		if (editor_completion_print_ask(e))
			editor_completion_print_col(e);
		print_prompt(e);
		ft_putstr(e->line);
		save = e->cur;
		e->cur = e->line_len;
		while (e->cur > save)
			move_cursor_left(e);
// */

	return (pos);
}

int		ft_outc(int c)
{
	ft_putchar(c);
	return (1);
}

void	close_line_edition(t_env *e)
{
	int		i;
	int		line_len;

	if (e->line_len <= 0)
		return ;
	line_len = e->line_len;
	i = (line_len + e->prompt_len) / e->ws_col;
	if (((line_len + e->prompt_len) % e->ws_col))
		i++;
	i *= e->ws_col;
	i -= e->cur + 1 + e->prompt_len;
	i /= e->ws_col;
	ft_putnchar(i, '\n');
}
