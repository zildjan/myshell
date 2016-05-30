/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_cursor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:46:21 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/30 20:23:33 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		move_cursor_right(t_env *e)
{
	int		nb;

	if (e->cur >= e->line_len)
		return (0);
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

int		move_cursor_left(t_env *e)
{
	int		i;
	int		nb;

	if (e->cur <= 0)
		return (0);
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
	move_cursor_left_char_parse(e, &nb);
	while (nb-- > 0)
		tputs(tgetstr("le", NULL), 0, ft_outc);
	return (1);
}

void	move_cursor_left_char_parse(t_env *e, int *nb)
{
	if (e->line[e->cur] == '\t')
	{
		*nb = (get_cur_pos(e, e->cur) % e->ws_col);
		*nb %= e->t.tab_len;
		*nb = e->t.tab_len - *nb;
		if (is_end_of_line(e, e->cur + 1))
			*nb = e->ws_col - (get_cur_pos(e, e->cur) % e->ws_col) - 1;
	}
	else if (e->line[e->cur] == '\n')
	{
		*nb = (get_cur_pos(e, e->cur) % e->ws_col);
		*nb = e->ws_col - *nb - 1;
	}
}

int		get_cur_pos(t_env *e, int cur)
{
	int		pos;
	int		i;

	pos = e->prompt_len;
	i = -1;
	while (++i < cur && i < e->line_len)
	{
		get_cur_pos_loop(e, &i, &pos);
	}
	return (pos);
}

void	get_cur_pos_loop(t_env *e, int *i, int *pos)
{
	int		tmp;

	if (e->line[*i] == '\t')
	{
		tmp = *pos % e->ws_col;
		if ((tmp + (e->ws_col % e->t.tab_len) >= e->ws_col)
			&& (e->ws_col % e->t.tab_len != 0))
			*pos += e->ws_col - tmp;
		else
		{
			tmp = tmp % e->t.tab_len;
			(*pos) += e->t.tab_len - tmp;
		}
	}
	else if (e->line[*i] == '\n')
	{
		tmp = *pos % e->ws_col;
		(*pos) += e->ws_col - tmp;
	}
	else
		(*pos)++;
}
