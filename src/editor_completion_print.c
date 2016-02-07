/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_completion_print.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 00:43:31 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/07 00:52:24 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	editor_completion_print(t_env *e)
{
	int		save;

	if (!e->compl->cur)
	{
		ft_putchar('\n');
		close_line_edition(e);
		if (editor_completion_print_ask(e))
			editor_completion_print_col(e);
		print_prompt(e);
		ft_putstr(e->line);
		save = e->cur;
		e->cur = e->line_len;
		while (e->cur > save)
			move_cursor_left(e);
	}
	else
	{
		e->compl->cur++;
		ft_putchar(7);
	}
}

int		editor_completion_print_ask(t_env *e)
{
	int		ok;
	char	buf;

	ok = 1;
	if (e->compl->size < 100)
		return (ok);
	ft_printf("Display all %d possibilities? (y or n)", e->compl->size);
	while (1)
	{
		read(0, &buf, 1);
		if (buf == 'y' || buf == ' ')
			break ;
		else if (buf == 'n' || buf == 3 || buf == 127)
		{
			ok = 0;
			break ;
		}
		else
			ft_putchar(7);
	}
	ft_putchar('\n');
	return (ok);
}

void	editor_completion_print_col(t_env *e)
{
	int		nb_col;
	int		col_h;
	int		i;
	int		line;

	nb_col = (e->ws_col - 1) / (e->compl->len_max + 2);
	col_h = (e->compl->size / nb_col);
	if (e->compl->size % nb_col)
		col_h++;
	line = -1;
	while (++line < col_h)
	{
		i = -1;
		while (++i < e->compl->size)
		{
			if (i % col_h == 0 && i + line < e->compl->size)
				editor_completion_print_one(e, i + line);
		}
		ft_putchar('\n');
	}
}

void	editor_completion_print_one(t_env *e, int id)
{
	int		len;
	char	*path;

	len = ft_putstr(e->compl->poss[id]);
	if (e->compl->path)
	{
		path = ft_strjoin(e->compl->path, e->compl->poss[id]);
		if (ft_get_lfile_type(path) == 'd')
			len += ft_putstr("/");
		free(path);
	}
	ft_putnspace(e->compl->len_max - len + 2);
}
