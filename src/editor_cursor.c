/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_cursor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:46:21 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/18 18:07:11 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		move_cursor_right(t_env *e)
{
	int		nb;

	if (e->cur < e->line_len)
	{
		e->cur++;

		nb = 1;
		if (e->line[e->cur - 1] == '\t')
		{
			nb = (get_cur_pos(e, e->cur - 1) % e->ws_col);
			nb %= e->t.tab_len;
			nb = e->t.tab_len - nb;
		}
		if (is_end_of_line(e, e->cur))
		{
			if (e->t.xn)
				tputs(tgetstr("do", NULL), 0, ft_outc);
			else
				tputs(tgetstr("nw", NULL), 0, ft_outc);
		}
		else
		{
			while (nb-- > 0)
				tputs(tgetstr("nd", NULL), 0, ft_outc);
		}
		return (1);
	}
	else
		return (0);
}

int		move_cursor_left(t_env *e)
{
	int		i;
	int		nb;

//	ft_printf("\nYEAH --> cur=%d\n", get_cur_pos(e, e->cur));

	if (e->cur > 0)
	{
		e->cur--;
		nb = 1;
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
			nb = 0;
		}
//*/
		if (e->line[e->cur] == '\t')
		{
			nb = (get_cur_pos(e, e->cur) % e->ws_col);
			nb %= e->t.tab_len;
			nb = e->t.tab_len - nb;

			if (is_end_of_line(e, e->cur + 1))
				nb = e->ws_col - (get_cur_pos(e, e->cur) % e->ws_col) - 1;
		}

//		ft_printf("\nnb=%ld cur=%ld w=%ld\n", nb, (get_cur_pos(e, e->cur) % e->ws_col), e->ws_col);
//		ft_printf("\nYEAH --> nb=%d\n", nb);

		while (nb-- > 0)
				tputs(tgetstr("le", NULL), 0, ft_outc);

		return (1);
	}
	else
		return (0);
}

void	refresh_eol(t_env *e)
{
	int		cur_save;

	ft_putstr(e->line + e->cur);
	cur_save = e->cur;
	e->cur = e->line_len;

//	ft_printf("\nYEAH --> cur=%d save=%d\n", e->cur, cur_save);

	if (is_end_of_line(e, e->line_len) && cur_save != e->line_len)
		e->cur--;

	while (cur_save < e->cur)
		move_cursor_left(e);

//	ft_putnchar(n, ' ');

//	move_cursor_back(e, 1, 0);
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
