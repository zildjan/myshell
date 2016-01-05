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


		if (ret == 3 && buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
		{
			if (e->cur > 0)
			{
				tputs(tgetstr("le", NULL), 0, ft_outc);
				e->cur--;
			}
			else
				ft_putchar(7);
		}
		else if (ret == 3 && buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
		{
			if (e->cur < e->line_len)
			{
				tputs(tgetstr("nd", NULL), 0, ft_outc);
				e->cur++;
			}
			else
				ft_putchar(7);
		}
		else if (ret == 3 && buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
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
		else if (ret == 3 && buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		{
			if (e->histo_cur)
			{
				e->histo_cur = e->histo_cur->down;
				switch_to_histo(e);
			}
			else
				ft_putchar(7);
		}
		else if (ret == 1 && buf[0] == 10)
		{
			ft_putchar('\n');
			break ;
		}
		else if (ret == 1 && buf[0] == 3)
		{
			ft_putchar('\n');
			ft_bzero(e->line, e->line_len);
			break ;
		}
		else if (ret == 1 && buf[0] == 4)
		{
			if (!e->line_len)
			{
				ft_putendl("exit");
				builtin_exit(e);
			}
			else
				ft_putchar(7);
		}
		else if (ret == 1 && buf[0] == 127)
		{
			if (e->cur > 0)
				delete_input_char(e);
			else
				ft_putchar(7);
		}
		else if (ret == 1 && ft_isprint(buf[0]))
			get_input_char(e, buf[0]);
		if (e->cur + 10 >= e->line_size)
		{
			char	refresh;

			refresh = 0;
			if (e->line_save == e->line)
				refresh = 1;
			e->line = ft_memrealloc(e->line, e->line_size, e->line_size + 10);
			if (refresh)
				e->line_save = e->line;
			e->line_size += 10;
		}
	}

//	ft_printf("buf=%s\n", e->line);
	if (e->line != e->line_save)
		free(e->line_save);
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

void	delete_input_char(t_env *e)
{
	int		i;
//	char	tmp;

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
