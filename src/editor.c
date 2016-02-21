/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:40:20 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/21 00:19:11 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		get_term_line_input(t_env *e, int eof_exit)
{
	char	buf[8];
	int		ret;

	e->cur = 0;
	e->line_len = 0;
	e->line_size = 100;
	e->line = (char*)ft_memalloc(sizeof(char) * e->line_size);
	e->line_save = e->line;
	e->histo_cur = NULL;
	while (1)
	{
		ft_bzero(buf, 8);
		ret = read(0, &buf, 7);
		if (!(ret = process_all_key(e, ret, buf, eof_exit)))
			get_input_chars(e, buf);
		if (ret == -1)
			break ;
		realloc_input_line(e);
	}
	if (e->line != e->line_save)
		free(e->line_save);
	close_line_edition(e);
	completion_free(e);

	history_save_ent(e, e->line);

	return (e->line_len);
}

int		process_all_key(t_env *e, int ret, char *buf, int eof_exit)
{
	char	*tmp;

	if (ret == 1 && buf[0] == 18)
	{
		tmp = editor_search(e);
		ft_strncpy(buf, tmp, 7);
		free(tmp);
		ret = ft_strlen(buf);
	}
	if (buf[1] == 91)
		buf[1] = 79;
	return (process_control_key(e, ret, buf, eof_exit));
}

void	get_input_chars(t_env *e, char *buf)
{
	while (ft_isprint(*buf))
	{
		if (*buf == '\t')
			*buf = ' ';
		get_input_char(e, *buf++);
	}
}

void	get_input_char(t_env *e, char c)
{
	int		i;
	char	tmp;
	char	tmp_pre;

	i = e->cur;
	tmp_pre = e->line[i++];
	while (tmp_pre)
	{
		tmp = e->line[i];
		e->line[i++] = tmp_pre;
		tmp_pre = tmp;
	}
	e->line[e->cur++] = c;
	e->line_len++;
	tputs(tgetstr("im", NULL), 0, ft_outc);
	if (!e->t.eo)
		tputs(tgetstr("ic", NULL), 0, ft_outc);
	ft_putchar(c);
	if (e->t.xn && is_end_of_line(e, e->cur))
		ft_putchar('\n');
	tputs(tgetstr("ip", NULL), 0, ft_outc);
	tputs(tgetstr("ei", NULL), 0, ft_outc);
	ft_putstr(e->line + e->cur);
	move_cursor_back(e, 0, 0);
	realloc_input_line(e);
}
