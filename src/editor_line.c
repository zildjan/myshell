/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 20:22:06 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/30 20:22:31 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	refresh_eol(t_env *e)
{
	int		cur_save;

	put_line(e, e->cur);
	cur_save = e->cur;
	e->cur = e->line_len;
	while (cur_save < e->cur)
	{
		move_cursor_left(e);
	}
}

void	put_line_char(t_env *e, int cur)
{
	ft_putchar(e->line[cur]);
	if (e->t.xn && is_end_of_line(e, cur + 1) && e->line[cur] != '\t'
		&& e->line[cur] != '\n')
	{
		if (e->t.xn)
			tputs(tgetstr("do", NULL), 0, ft_outc);
		else
			tputs(tgetstr("nw", NULL), 0, ft_outc);
	}
}

void	put_line(t_env *e, int start)
{
	while (e->line[start] && start <= e->line_len)
		put_line_char(e, start++);
}
