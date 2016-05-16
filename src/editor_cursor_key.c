/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_cursor_key.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:44:00 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/16 19:11:30 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		process_cursor_key(t_env *e, int ret, char *buf)
{
	if (ft_strequ(buf, e->t.kl))
	{
		if (!move_cursor_left(e))
			ft_putchar(7);
	}
	else if (ft_strequ(buf, e->t.kr))
	{
		if (!move_cursor_right(e))
			ft_putchar(7);
	}
	else
		return (process_cursor2_key(e, ret, buf));
	return (1);
}

int		process_cursor2_key(t_env *e, int ret, char *buf)
{
	int		i;

	i = e->ws_col;
	if (ft_strequ(buf, e->t.kh_s))
	{
		while (e->cur > 0 && i--)
			move_cursor_left(e);
	}
	else if (ft_strequ(buf, e->t.ke_s))
	{
		while (e->cur < e->line_len && i--)
			move_cursor_right(e);
	}
	else
		return (process_home_end_key(e, ret, buf));
	return (1);
}

int		process_home_end_key(t_env *e, int ret, char *buf)
{
	if (ft_strequ(buf, e->t.kh))
	{
		while (e->cur > 0)
			move_cursor_left(e);
	}
	else if (ft_strequ(buf, e->t.ke))
	{
		while (e->cur < e->line_len)
			move_cursor_right(e);
	}
	else
		return (process_prev_word_key(e, ret, buf));
	return (1);
}

int		process_prev_word_key(t_env *e, int ret, char *buf)
{
	if (ft_strequ(buf, e->t.kl_s))
	{
		if (e->cur > 0)
			while (e->cur > 0 && is_aspace(e->line[e->cur - 1]))
				move_cursor_left(e);
		if (e->cur > 0)
			while (e->cur > 0 && !is_aspace(e->line[e->cur - 1]))
				move_cursor_left(e);
	}
	else
		return (process_next_word_key(e, ret, buf));
	return (1);
}

int		process_next_word_key(t_env *e, int ret, char *buf)
{
	if (ft_strequ(buf, e->t.kr_s))
	{
		while (e->cur < e->line_len && is_aspace(e->line[e->cur]))
			move_cursor_right(e);
		while (e->cur < e->line_len && !is_aspace(e->line[e->cur]))
			move_cursor_right(e);
	}
	else
		return (process_edition_key(e, ret, buf));
	return (1);
}
