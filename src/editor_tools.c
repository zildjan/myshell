/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 16:47:23 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/02 22:46:28 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	realloc_input_line(t_env *e)
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

int		is_end_of_line(t_env *e, int cur)
{
	if (!((cur + e->prompt_len) % e->ws_col))
	{
		return (1);
	}
	return (0);
}

int		get_cur_pos(t_env *e, int cur)
{
	int		pos;
	int		i;
	int		tmp;

	pos = e->prompt_len;
	i = -1;
	while (++i <= cur && i <= e->line_len)
	{
		if (e->line[i] == '\t')
		{
			tmp = pos % e->ws_col;
			tmp = tmp % e->t.tab_len;
			pos += e->t.tab_len - tmp;
		}
		else
			pos++;
	}	
	return (pos);
}

int		ft_outc(int c)
{
	ft_putchar(c);
	return (1);
}

void	close_line_edition(t_env *e)
{
	int		i;
	int		line_len;

	if (e->line_len <= 0)
		return ;
	line_len = e->line_len;
	i = (line_len + e->prompt_len) / e->ws_col;
	if (((line_len + e->prompt_len) % e->ws_col))
		i++;
	i *= e->ws_col;
	i -= e->cur + 1 + e->prompt_len;
	i /= e->ws_col;
	ft_putnchar(i, '\n');
}
