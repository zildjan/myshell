/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_control_key.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:42:30 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/20 23:45:07 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		process_control_key(t_env *e, int ret, char *buf, int eof_exit)
{
	if (ret == 1 && buf[0] == 4)
	{
		if (!e->line_len && eof_exit)
		{
			ft_putendl("exit");
			builtin_exit(e);
		}
		else if (!eof_exit)
		{
			ft_putchar('\n');
			close_line_edition(e);
			ft_bzero(e->line, e->line_len);
			e->line_len = -1;
			return (-1);
		}
		else
			ft_putchar(7);
	}
	else
		return (process_break_key(e, ret, buf));
	return (1);
}

int		process_break_key(t_env *e, int ret, char *buf)
{
	if (ret == 1 && buf[0] == 10)
	{
//		t_parse	*l;

//	if (p->quo && !p->escape)
//		p->buf[p->ib++] = '\n';

//		p->error = get_cmd_end(e, p->separ);

		ft_putchar('\n');

//		if ()
		return (-1);
	}
	else if (ret == 1 && buf[0] == 3)
	{
		ft_putchar('\n');
		close_line_edition(e);
		ft_bzero(e->line, e->line_len);
		e->line_len = -2;
		return (-1);
	}
	else
		return (process_completion_key(e, ret, buf));
}

int		process_completion_key(t_env *e, int ret, char *buf)
{
	if (ret == 1 && buf[0] == 9)
	{
		editor_completion(e);
	}
	else
		return (process_cursor_key(e, ret, buf));
	return (1);
}
