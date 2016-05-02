/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_cursor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:46:21 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/02 22:56:23 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		move_cursor_right(t_env *e)
{
	if (e->cur < e->line_len)
	{
		e->cur++;
		if (is_end_of_line(e, e->cur))
		{
			if (e->t.xn)
				tputs(tgetstr("do", NULL), 0, ft_outc);
			else
				tputs(tgetstr("nw", NULL), 0, ft_outc);
		}
		else
		{
			int		nb;

			nb = 1;
			if (e->line[e->cur - 1] == '\t')
			{
				nb = (get_cur_pos(e, e->cur - 1) % e->ws_col);
				nb %= e->t.tab_len;
				nb = e->t.tab_len - nb;
			}
			while (nb--)
				tputs(tgetstr("nd", NULL), 0, ft_outc);
		}
		return (1);
	}
	else
		return (0);
}

int		move_cursor_left(t_env *e)
{
	int i;

	if (e->cur > 0)
	{
		e->cur--;
		if (is_end_of_line(e, e->cur + 1))
		{
			tputs(tgetstr("up", NULL), 0, ft_outc);
			if (e->t.mi)
				tputs(tgoto(tgetstr("ch", NULL), 0, e->ws_col - 1), 0, ft_outc);
			else
			{
				i = e->ws_col;
				while (i--)
					tputs(tgetstr("nd", NULL), 0, ft_outc);
			}
		}
		else
		{
			int		nb;

			nb = 1;
			if (e->line[e->cur] == '\t')
			{
				nb = (get_cur_pos(e, e->cur - 1) % e->ws_col);
				nb %= e->t.tab_len;
				nb = e->t.tab_len - nb;
			}
			while (nb--)
				tputs(tgetstr("le", NULL), 0, ft_outc);
		}
		return (1);
	}
	else
		return (0);
}

void	move_cursor_back(t_env *e, char delete, int i)
{
	i = e->line_len - e->cur;
	if (is_end_of_line(e, e->line_len))
		i--;
	if (is_end_of_line(e, e->line_len) && !i)
	{
		tputs(tgetstr("le", NULL), 0, ft_outc);
		tputs(tgetstr("nd", NULL), 0, ft_outc);
	}
	if (!e->t.xn && delete && is_end_of_line(e, e->line_len))
	{
		tputs(tgetstr("up", NULL), 0, ft_outc);
		tputs(tgoto(tgetstr("ch", NULL), 0, e->ws_col - 1), 0, ft_outc);
	}
	while (i-- > 0)
	{
		if (!e->t.xn && is_end_of_line(e, e->cur + i)
			&& !is_end_of_line(e, e->cur))
		{
			tputs(tgetstr("up", NULL), 0, ft_outc);
			tputs(tgoto(tgetstr("ch", NULL), 0, e->ws_col - 1), 0, ft_outc);
		}
		else if (e->t.xn
				|| (!e->t.xn && !is_end_of_line(e, e->cur + i + 1)))
			tputs(tgetstr("le", NULL), 0, ft_outc);
	}
}
