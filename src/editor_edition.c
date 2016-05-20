/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_edition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:49:14 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/20 19:39:41 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	tputs(tgetstr("ed", NULL), 0, ft_outc);

	e->line_len -= n;

	refresh_eol(e);
}

void	backdelete_input_char(t_env *e)
{
	int		i;

	i = e->cur - 1;
	move_cursor_left(e);

	tputs(tgetstr("dm", NULL), 0, ft_outc);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	tputs(tgetstr("ed", NULL), 0, ft_outc);

	while (e->line[i])
	{
		e->line[i] = e->line[i + 1];
		i++;
	}

	e->line_len--;
	refresh_eol(e);
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
		realloc_input_line(e);
	}
}

void	switch_to_histo(t_env *e)
{
	while (e->cur > 0)
		move_cursor_left(e);
	tputs(tgetstr("dm", NULL), 0, ft_outc);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	tputs(tgetstr("ed", NULL), 0, ft_outc);

	if (e->line != e->line_save)
		free(e->line);
	if (e->histo_cur)
		e->line = ft_strdup(e->histo_cur->line);
	else
		e->line = e->line_save;

	e->line_len = ft_strlen(e->line);
	e->line_size = e->line_len;
	e->cur = e->line_len;

	put_line(e, 0);
}
