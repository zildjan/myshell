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
	{
//		ft_printf("GET\n");
		get_term_input(e);
		return ;
	}
	ret = get_next_line(0, &e->line);
	if (ret == 0)
	{
		ft_printf("exit\n");
		builtin_exit(e);
	}
	if (!e->line)
		e->line = ft_strdup("");
}

void	get_term_input(t_env *e)
{
	char	buf[8];
	int		ret;

	char *key_r;
	char *key_l;
	key_r = ft_strnew(100);
	key_l = ft_strnew(100);
	key_r = tgetstr("kr", NULL);
	key_l = tgetstr("kl", NULL);
	ft_printf("'%d' '%d' '%d' '%d' '%d' '%d' '%d' '%d' '%d' '%d' '%d' '%d' '%d' '%d' '%d' '%d' '%d' '%d' '%d'- ", 
			  key_r[0], key_r[1],
			  key_r[2], key_r[3], key_r[4], key_r[5], key_r[6], key_r[7], key_r[8],
			  key_r[9], key_r[10], key_r[11], key_r[12], key_r[13], key_r[14], key_r[15], key_r[16], key_r[17], key_r[18]);
	ft_printf("'%c' '%c' '%c' '%c' '%c'\n", key_r[0], key_r[1], key_r[2], key_r[3], key_r[4]);
	e->cur = 0;
	e->line_len = 0;
	e->line_size = 100 + 1000;
	e->line = (char*)ft_memalloc(sizeof(char) * e->line_len);
	while (1)
	{
		ft_bzero(buf, 8);
		ret = read(0, &buf, 7);
//		ft_printf("%d %d %d %d %d %d %d - ", buf[0], buf[1], buf[2],
//				  buf[3], buf[4], buf[5], buf[6]);
//		ft_printf("'%c' '%c' '%c' '%c' '%c' '%c' '%c' =%d\n", buf[0], buf[1],
//				  buf[2], buf[3], buf[4], buf[5], buf[6], ret);


		if (!ft_strcmp(buf, key_l))
		{
			if (e->cur > 0)
			{
				tputs(tgetstr("le", NULL), 0, ft_outc);
				e->cur--;
			}
		}
		else if (!ft_strcmp(buf, key_r))
		{
			if (e->cur < e->line_len)
			{
				tputs(tgetstr("nd", NULL), 0, ft_outc);
				e->cur--;
			}
		}
		else if (ret == 1 && buf[0] == 10)
		{
			ft_putchar('\n');
			break ;
		}
		else if (ret == 1 && buf[0] == 4)
		{
			ft_putendl("exit");
			builtin_exit(e);
		}
		else if (ret == 1 && ft_isprint(buf[0]))
			get_input_char(e, buf[0]);
	}
}

void	get_input_char(t_env *e, char c)
{
	e->line[e->cur++] = c;
	e->line_len++;
	ft_putchar(c);
}

int		ft_outc(int c)
{
	ft_putchar(c);
	return (1);
}
