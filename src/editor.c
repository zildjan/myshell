/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:40:20 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/30 00:20:40 by pbourrie         ###   ########.fr       */
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
	completion_free(e);
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
	while (ft_isprint(*buf) || is_aspace(*buf) || *buf == -115 || *buf == -119)
	{
		if (*buf == -115)
			*buf = '\n';
		else if (*buf == -119)
			*buf = '\t';
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
	tputs(tgetstr("dm", NULL), 0, ft_outc);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	tputs(tgetstr("ed", NULL), 0, ft_outc);
	tputs(tgetstr("im", NULL), 0, ft_outc);
	if (!e->t.eo)
		tputs(tgetstr("ic", NULL), 0, ft_outc);
	put_line_char(e, e->cur - 1);
	tputs(tgetstr("ip", NULL), 0, ft_outc);
	tputs(tgetstr("ei", NULL), 0, ft_outc);
	refresh_eol(e);
	realloc_input_line(e);
}
