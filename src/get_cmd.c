/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/08 02:23:04 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	get_cmd(t_env *e)
{
	get_input_line(e);
	if (e->line == NULL)
		return ;
	parse_cmd(e);
	free(e->line);
	e->line = NULL;
}

void	get_cmd_end(t_env *e, char type)
{
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
	get_input_line(e);
}

void	get_input_line(t_env *e)
{
	int		ret;

	if (e->term)
		get_term_line_input(e);
	else
	{
		ret = get_next_line(0, &e->line);
		if (ret == 0)
		{
			ft_printf("exit\n");
			builtin_exit(e);
		}
	}
	if (!e->line)
		e->line = ft_strdup("");
}

void	get_term_line_input(t_env *e)
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
		if (process_all_key(e, ret, buf))
			(void)e;
		else if (process_break_key(e, ret, buf))
			break ;
		else
			get_input_chars(e, buf);
		resize_input_line(e);
	}
	if (e->line != e->line_save)
		free(e->line_save);
	close_line_edition(e);
}

int		process_all_key(t_env *e, int ret, char *buf)
{
	if (ret == 3 && buf[1] == 91)
		buf[1] = 79;
	else if (ret == 4 && buf[2] == 91)
		buf[2] = 79;
	if (!process_cursor_key(e, ret, buf))
		return (0);
	return (1);
}

int		process_break_key(t_env *e, int ret, char *buf)
{
	if (ret == 1 && buf[0] == 10)
		ft_putchar('\n');
	else if (ret == 1 && buf[0] == 3)
	{
		ft_putchar('\n');
		ft_bzero(e->line, e->line_len);
	}
	else
		return (0);
	return (1);
}

int		process_cursor_key(t_env *e, int ret, char *buf)
{
	if (ft_strequ(buf, tgetstr("kl", NULL)))
	{
		if (!move_cursor_left(e))
			ft_putchar(7);
	}
	else if (ft_strequ(buf, tgetstr("kr", NULL)))
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
	if (ft_strequ(buf, tgetstr("#2", NULL)))
	{
		while (e->cur > 0 && i--)
			move_cursor_left(e);
	}
	else if (ft_strequ(buf, tgetstr("*7", NULL)))
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
	if (ft_strequ(buf, tgetstr("kh", NULL)))
	{
		while (e->cur > 0)
			move_cursor_left(e);
	}
	else if (ft_strequ(buf, tgetstr("@7", NULL)))
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
	if (ft_strequ(buf, tgetstr("#4", NULL)))
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
	if (ft_strequ(buf, tgetstr("%i", NULL)))
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
			backdelete_input_char(e);
		else
			ft_putchar(7);
	}
	else if (ft_strequ(buf, tgetstr("kD", NULL)))
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
		return (process_histo_up_key(e, ret, buf));
	return (1);
}

int		process_histo_up_key(t_env *e, int ret, char *buf)
{
	if (ft_strequ(buf, tgetstr("ku", NULL)))
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
		return (process_histo_down_key(e, ret, buf));
	return (1);
}

int		process_histo_down_key(t_env *e, int ret, char *buf)
{
	if (ft_strequ(buf, tgetstr("kd", NULL)))
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
		return (process_option_key(e, ret, buf));
	return (1);
}

int		process_option_key(t_env *e, int ret, char *buf)
{
	if (ret == 1 && buf[0] == 4)
	{
		if (!e->line_len)
		{
			ft_putendl("exit");
			builtin_exit(e);
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
			tputs(tgetstr("do", NULL), 0, ft_outc);
		else
			tputs(tgetstr("nd", NULL), 0, ft_outc);
		return (1);
	}
	else
		return (0);
}

int		move_cursor_left(t_env *e)
{
	if (e->cur > 0)
	{
		e->cur--;
		if (is_end_of_line(e, e->cur + 1))
		{
			tputs(tgetstr("up", NULL), 0, ft_outc);
			tputs(tgoto(tgetstr("ch", NULL), 0, e->ws_col - 1), 0, ft_outc);
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
	tputs(tgetstr("ic", NULL), 0, ft_outc);
	ft_putchar(c);
	if (is_end_of_line(e, e->cur))
		ft_putchar('\n');
	tputs(tgetstr("ip", NULL), 0, ft_outc);
	tputs(tgetstr("ei", NULL), 0, ft_outc);
	ft_putstr(e->line + e->cur);
	i = e->line_len - e->cur;
	if (is_end_of_line(e, e->line_len))
		i--;
	while (i-- > 0)
		tputs(tgetstr("le", NULL), 0, ft_outc);
}

int		is_end_of_line(t_env *e, int cur)
{
	if (!((cur + e->prompt_len) % e->ws_col))
	{
		return (1);
	}
	return (0);
}

void	backdelete_input_char(t_env *e)
{
	int		i;

	i = e->cur - 1;
	while (e->line[i])
	{
		e->line[i] = e->line[i + 1];
		i++;
	}
	move_cursor_left(e);
	tputs(tgetstr("dm", NULL), 0, ft_outc);
	tputs(tgetstr("dc", NULL), 0, ft_outc);
	tputs(tgetstr("ed", NULL), 0, ft_outc);
	ft_putstr(e->line + e->cur);
	ft_putchar(' ');
	i = e->line_len - e->cur;
	if (is_end_of_line(e, e->line_len))
		i--;
	if (is_end_of_line(e, e->line_len) && !i)
	{
		tputs(tgetstr("le", NULL), 0, ft_outc);
		tputs(tgetstr("nd", NULL), 0, ft_outc);
	}
	while (i-- > 0)
		tputs(tgetstr("le", NULL), 0, ft_outc);
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
	i = e->line_len - e->cur;
	if (is_end_of_line(e, e->line_len))
		i--;
	while (i-- > 0)
		tputs(tgetstr("le", NULL), 0, ft_outc);
	e->line_len -= n;
}

void	switch_to_histo(t_env *e)
{
	while (e->cur < e->line_len)
		move_cursor_right(e);
	while (e->cur)
	{
		tputs(tgetstr("le", NULL), 0, ft_outc);
		tputs(tgetstr("dm", NULL), 0, ft_outc);
		tputs(tgetstr("dc", NULL), 0, ft_outc);
		tputs(tgetstr("ed", NULL), 0, ft_outc);
		e->cur--;
	}
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
