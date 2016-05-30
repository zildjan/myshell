/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:47:23 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/30 20:23:35 by pbourrie         ###   ########.fr       */
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
	if (!((get_cur_pos(e, cur)) % e->ws_col))
	{
		return (1);
	}
	return (0);
}

int		ft_outc(int c)
{
	ft_putchar(c);
	return (1);
}

void	close_line_edition(t_env *e)
{
	while (e->cur < e->line_len)
	{
		move_cursor_right(e);
	}
	ft_putchar('\n');
}
