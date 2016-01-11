/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/11 01:38:32 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	get_cmd(t_env *e)
{
	get_input_line(e, 1);
	if (e->line == NULL)
		return ;
	parse_cmd(e);
	free(e->line);
	e->line = NULL;
}

int		get_cmd_end(t_env *e, char type)
{
	int		ret;

	if (e->line)
		free(e->line);
	e->line = NULL;
	if (type == SEP_PIPE)
		ft_putstr("pipe> ");
	else if (type == SEP_AND)
		ft_putstr("cmdand> ");
	else if (type == SEP_OR)
		ft_putstr("or> ");
	else if (type == '\'')
		ft_putstr("quote> ");
	else if (type == '"')
		ft_putstr("dquote> ");
	else
		ft_putstr("> ");
	ret = get_input_line(e, 0);
	if (ret == -1 && type)
		return (EP_EOF);
	if (ret == -2)
		return (100);
	return (0);
}

int		get_input_line(t_env *e, int eof_exit)
{
	int		ret;

	if (e->term)
		ret = get_term_line_input(e, eof_exit);
	else
	{
		ret = get_next_line(0, &e->line);
		if (ret == 0 && eof_exit)
		{
			ft_printf("exit\n");
			builtin_exit(e);
		}
		else if (ret == 0)
			ret = -1;
		if (!e->line)
			e->line = ft_strdup("");
	}
//	ft_printf("ret=%d\n", ret);
	return (ret);
}

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
		resize_input_line(e);
	}
	if (e->line != e->line_save)
		free(e->line_save);
	close_line_edition(e);
	return (e->line_len);
}

int		process_all_key(t_env *e, int ret, char *buf, int eof_exit)
{
	if (buf[1] == 91)
		buf[1] = 79;
	return (process_option_key(e, ret, buf, eof_exit));
}

int		process_option_key(t_env *e, int ret, char *buf, int eof_exit)
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
		ft_putchar('\n');
		return (-1);
	}
	else if (ret == 1 && buf[0] == 3)
	{
		ft_putchar('\n');
		ft_bzero(e->line, e->line_len);
		e->line_len = -2;
		return (-1);
	}
	else
		return (process_cursor_key(e, ret, buf));
}

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
			while (e->cur > 0 && e->line[e->cur - 1] == ' ')
				move_cursor_left(e);
		if (e->cur > 0)
			while (e->cur > 0 && e->line[e->cur - 1] != ' ')
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
		while (e->cur < e->line_len && e->line[e->cur] == ' ')
			move_cursor_right(e);
		while (e->cur < e->line_len && e->line[e->cur] != ' ')
			move_cursor_right(e);
	}
	else
		return (process_edition_key(e, ret, buf));
	return (1);
}

int		process_edition_key(t_env *e, int ret, char *buf)
{
	if (ret == 1 && buf[0] == 127)
	{
		if (e->cur > 0)
			backdelete_input_char(e, 0);
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
			tputs(tgetstr("nd", NULL), 0, ft_outc);
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
			tputs(tgetstr("le", NULL), 0, ft_outc);
		return (1);
	}
	else
		return (0);
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
}

int		is_end_of_line(t_env *e, int cur)
{
	if (!((cur + e->prompt_len) % e->ws_col))
	{
		return (1);
	}
	return (0);
}

void	backdelete_input_char(t_env *e, char no_mem)
{
	int		i;

	i = e->cur - 1;
	while (!no_mem && e->line[i])
	{
		e->line[i] = e->line[i + 1];
		i++;
	}
	move_cursor_left(e);
	tputs(tgetstr("dm", NULL), 0, ft_outc);
	tputs(tgetstr("dc", NULL), 0, ft_outc);
	tputs(tgetstr("ed", NULL), 0, ft_outc);
	if (!no_mem)
		ft_putstr(e->line + e->cur);
	ft_putchar(' ');
	move_cursor_back(e, 1, 0);
	e->line_len--;
}

void	delete_input_char(t_env *e)
{
	int		i;

	tputs(tgetstr("vi", NULL), 0, ft_outc);
	i = e->cur;
	while (e->line[i])
	{
		e->line[i] = e->line[i + 1];
		i++;
	}
	tputs(tgetstr("dm", NULL), 0, ft_outc);
	tputs(tgetstr("dc", NULL), 0, ft_outc);
	tputs(tgetstr("ed", NULL), 0, ft_outc);
	ft_putstr(e->line + e->cur);
	ft_putchar(' ');
	i = e->line_len - e->cur;
	if (is_end_of_line(e, e->line_len))
		i--;
	while (i-- > 0)
		tputs(tgetstr("le", NULL), 0, ft_outc);
	e->line_len--;
	tputs(tgetstr("ve", NULL), 0, ft_outc);
}

void	delete_input_nchar(t_env *e, int n)
{
	int		i;

	if (e->line_len - e->cur < n)
		n = e->line_len - e->cur;
	if (!n)
		return ;
	i = e->cur;
	while (e->line[i])
	{
		if (i + n - 1 <= e->line_len)
			e->line[i] = e->line[i + n];
		else
			e->line[i] = 0;
		i++;
	}
	tputs(tgetstr("dm", NULL), 0, ft_outc);
	i = n;
	while (i--)
		tputs(tgetstr("dc", NULL), 0, ft_outc);
	tputs(tgetstr("ed", NULL), 0, ft_outc);
	ft_putstr(e->line + e->cur);
	ft_putnchar(n, ' ');
	move_cursor_back(e, 1, 0);
	e->line_len -= n;
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

void	switch_to_histo(t_env *e)
{
	while (e->cur < e->line_len)
		move_cursor_right(e);
	while (e->cur)
		backdelete_input_char(e, 1);
	if (e->line != e->line_save)
		free(e->line);
	if (e->histo_cur)
		e->line = ft_strdup(e->histo_cur->line);
	else
		e->line = e->line_save;
	ft_putstr(e->line);
	e->line_len = ft_strlen(e->line);
	e->line_size = e->line_len;
	e->cur = e->line_len;
}

int		ft_outc(int c)
{
	ft_putchar(c);
	return (1);
}

void	cut_input_line(t_env *e)
{
	char	*cpy;
	int		i;
	int		len;

	cpy = e->line + e->cur;
	if (e->clipboard)
		free(e->clipboard);
	e->clipboard = ft_strdup(cpy);
	i = -1;
	len = ft_strlen(e->clipboard);
	delete_input_nchar(e, len);
}

void	paste_input_line(t_env *e)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	if (e->clipboard)
		len = ft_strlen(e->clipboard);
	if (len == 0)
		ft_putchar(7);
	while (++i < len)
	{
		get_input_char(e, e->clipboard[i]);
		resize_input_line(e);
	}
}

void	resize_input_line(t_env *e)
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

void	refresh_nb_col(t_env *e)
{
	struct winsize win;

	if (ioctl(1, TIOCGWINSZ, &win) == 0)
		e->ws_col = win.ws_col;
	else
		e->ws_col = 80;
}

void	close_line_edition(t_env *e)
{
	int		i;

	i = (e->line_len + e->prompt_len) / e->ws_col;
	if (((e->line_len + e->prompt_len) % e->ws_col))
		i++;
	i *= e->ws_col;
	i -= e->cur + 1 + e->prompt_len;
	i /= e->ws_col;
	ft_putnchar(i, '\n');
}
