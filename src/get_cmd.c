/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 21:54:46 by pbourrie         ###   ########.fr       */
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
//	ft_printf("GET END\n");
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
		get_term_input(e);
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

void	get_term_input(t_env *e)
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
//		ft_printf("%d %d %d %d %d %d %d - ", buf[0], buf[1], buf[2],
//				  buf[3], buf[4], buf[5], buf[6]);
//		ft_printf("'%c' '%c' '%c' '%c' '%c' '%c' '%c' =%d\n", buf[0], buf[1],
//				  buf[2], buf[3], buf[4], buf[5], buf[6], ret);

		if (process_all_key(e, ret, buf))	
			(void)e;
		else if (process_break_key(e, ret, buf))	
			break ;
		else if (ret == 1 && ft_isprint(buf[0]))
			get_input_char(e, buf[0]);
		resize_input_line(e);
	}
	if (e->line != e->line_save)
		free(e->line_save);
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
		if (e->cur > 0)
		{
			tputs(tgetstr("le", NULL), 0, ft_outc);
			e->cur--;
		}
		else
			ft_putchar(7);
	}
	else if (ft_strequ(buf, tgetstr("kr", NULL)))
	{
		if (e->cur < e->line_len)
		{
			e->cur++;
			if (!(e->cur % (e->ws_col - e->prompt_len)))
				tputs(tgetstr("do", NULL), 0, ft_outc);
			else
				tputs(tgetstr("nd", NULL), 0, ft_outc);
		}
		else
			ft_putchar(7);
	}
	else
		return (process_cursor2_key(e, ret, buf));
	return (1);
}

int		process_cursor2_key(t_env *e, int ret, char *buf)
{
	int		i;

	i = tgetnum("co");
	if (ft_strequ(buf, tgetstr("#2", NULL)))
	{
		while (e->cur > 0 && i)
		{
			tputs(tgetstr("le", NULL), 0, ft_outc);
			e->cur--;
			i--;
		}
	}
	else if (ft_strequ(buf, tgetstr("*7", NULL)))
	{
		while (e->cur < e->line_len && i)
		{
			tputs(tgetstr("nd", NULL), 0, ft_outc);
			e->cur++;
			i--;
		}
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
		{
			tputs(tgetstr("le", NULL), 0, ft_outc);
			e->cur--;
		}
	}
	else if (ft_strequ(buf, tgetstr("@7", NULL)))
	{
		while (e->cur < e->line_len)
		{
			tputs(tgetstr("nd", NULL), 0, ft_outc);
			e->cur++;
		}
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
			{
				tputs(tgetstr("le", NULL), 0, ft_outc);
				e->cur--;
			}
		if (e->cur > 0)
			while (e->cur > 0 && e->line[e->cur - 1] != ' ')
			{
				tputs(tgetstr("le", NULL), 0, ft_outc);
				e->cur--;
			}
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
		{
			tputs(tgetstr("nd", NULL), 0, ft_outc);
			e->cur++;
		}
		while (e->cur < e->line_len  && e->line[e->cur] != ' ')
		{
			tputs(tgetstr("nd", NULL), 0, ft_outc);
			e->cur++;
		}
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
			delete_input_char(e);
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
		e->line[i] = tmp_pre;
		tmp_pre = tmp;
		i++;
	}
	e->line[e->cur++] = c;
	e->line_len++;
	tputs(tgetstr("im", NULL), 0, ft_outc);
	tputs(tgetstr("ic", NULL), 0, ft_outc);
	ft_putchar(c);
	tputs(tgetstr("ip", NULL), 0, ft_outc);
	tputs(tgetstr("ei", NULL), 0, ft_outc);
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
	e->cur--;
	e->line_len--;
	tputs(tgetstr("le", NULL), 0, ft_outc);
	tputs(tgetstr("dm", NULL), 0, ft_outc);
	tputs(tgetstr("dc", NULL), 0, ft_outc);
	tputs(tgetstr("ed", NULL), 0, ft_outc);
}

void	delete_input_char(t_env *e)
{
	int		i;

	i = e->cur;
	while (e->line[i])
	{
		e->line[i] = e->line[i + 1];
		i++;
	}
	e->line_len--;
	tputs(tgetstr("dm", NULL), 0, ft_outc);
	tputs(tgetstr("dc", NULL), 0, ft_outc);
	tputs(tgetstr("ed", NULL), 0, ft_outc);
}

void	switch_to_histo(t_env *e)
{
	while (e->cur++ < e->line_len)
		tputs(tgetstr("nd", NULL), 0, ft_outc);
	e->cur--;
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
	while (++i < len)
		delete_input_char(e);
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
