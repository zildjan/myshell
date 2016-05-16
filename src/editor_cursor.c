/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_cursor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:46:21 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/16 22:50:45 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		move_cursor_right(t_env *e)
{
	if (e->cur < e->line_len)
	{
		e->cur++;
		int		nb;
		
		nb = 1;
		if (e->line[e->cur - 1] == '\t')
		{
			nb = (get_cur_pos(e, e->cur - 1) % e->ws_col);
			nb %= e->t.tab_len;
			nb = e->t.tab_len - nb;
		}
//		while (nb--)
//		{
//			if (!((get_cur_pos(e, e->cur) + nb) % e->ws_col))

		if (is_end_of_line(e, e->cur))
		{
			//		ft_printf("\nYEAH");
			if (e->t.xn)
				tputs(tgetstr("do", NULL), 0, ft_outc);
			else
				tputs(tgetstr("nw", NULL), 0, ft_outc);
		}
		else
		{
			while (nb-- > 0)
			{
				tputs(tgetstr("nd", NULL), 0, ft_outc);
			}
		}
		return (1);
	}
	else
		return (0);
}

int		move_cursor_left(t_env *e)
{
	int i;
	int		nb;

//	ft_printf("\ncur=%d w=%d\n", get_cur_pos(e, e->cur), e->ws_col);

	if (e->cur > 0)
	{
		e->cur--;


		nb = 1;

		
		if (is_end_of_line(e, e->cur + 1))
//			if (!((get_cur_pos(e, e->cur) + nb) % e->ws_col))
		{
//			ft_printf("\nYEAH -->\n");
			tputs(tgetstr("up", NULL), 0, ft_outc);

			if (e->t.mi)
			{
				tputs(tgoto(tgetstr("ch", NULL), 0, e->ws_col - 1), 0, ft_outc);
			}
			else
			{
				i = e->ws_col;
				while (i--)
					tputs(tgetstr("nd", NULL), 0, ft_outc);
			}
			nb = 0;
		}

		if (e->line[e->cur] == '\t')
		{
			nb = (get_cur_pos(e, e->cur) % e->ws_col);
			nb %= e->t.tab_len;
			nb = e->t.tab_len - nb;

			if (is_end_of_line(e, e->cur + 1))
				nb = e->ws_col - (get_cur_pos(e, e->cur) % e->ws_col) - 1;

//			if (is_end_of_line(e, e->cur + 1))
//				nb = (e->ws_col % e->t.tab_len) - 1;
		}
//		if (nb < 0)
//			nb = e->t.tab_len - 1;

//		ft_printf("\ncur=%ld w=%ld\n", get_cur_pos(e, e->cur), e->ws_col);
//		ft_printf("\nnb=%ld cur=%ld w=%ld\n", nb, (get_cur_pos(e, e->cur) % e->ws_col), e->ws_col);

//		ft_printf("\nYEAH --> nb=%d\n", nb);

		while (nb-- > 0)
		{
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
