/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_edition_key.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:45:30 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/20 19:31:31 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		process_edition_key(t_env *e, int ret, char *buf)
{
	if (ret == 1 && buf[0] == 127)
	{
		if (e->cur > 0)
			backdelete_input_char(e);
		else
			ft_putchar(7);
	}
	else if (ft_strequ(buf, e->t.ksup))
	{
		if (e->cur < e->line_len)
			delete_input_nchar(e, 1);
		else
			ft_putchar(7);
	}
	else if (ret == 1 && buf[0] == 11)
		cut_input_line(e);
	else if (ret == 1 && buf[0] == 25)
		paste_input_line(e);
	else
		return (process_histo_up_key(e, buf));
	return (1);
}

int		process_histo_up_key(t_env *e, char *buf)
{
	if (ft_strequ(buf, e->t.ku))
	{
		if (!e->histo_cur)
		{
			e->histo_cur = e->histo;
			switch_to_histo(e);
		}
		else if (e->histo_cur->up)
		{
			e->histo_cur = e->histo_cur->up;
			switch_to_histo(e);
		}
		else
			ft_putchar(7);
	}
	else
		return (process_histo_down_key(e, buf));
	return (1);
}

int		process_histo_down_key(t_env *e, char *buf)
{
	if (ft_strequ(buf, e->t.kd))
	{
		if (e->histo_cur)
		{
			e->histo_cur = e->histo_cur->down;
			switch_to_histo(e);
		}
		else
			ft_putchar(7);
	}
	else
		return (0);
	return (1);
}
