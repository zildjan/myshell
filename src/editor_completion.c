/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 23:00:22 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/04 01:46:58 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	editor_completion(t_env *e)
{
	completion_update(e);

	if (e->compl->size == 0)
		ft_putchar(7);
	else if (e->compl->size == 1)
	{
		char	*path;
		char	*comp;

		comp = e->compl->poss[0] + ft_strlen(e->compl->cstart);

		if (e->compl->lex.quo == NONE)
			path = ft_escape_chars(comp, " ;|\t\n><\\&'\"$");
		else if (e->compl->lex.quo == DOUB)
			path = ft_escape_chars(comp, "\\\"$");
		else
			path = ft_strdup(comp);
		get_input_chars(e, path);
		free(path);

		if (e->compl->lex.quo == DOUB)
			get_input_char(e, '"');
		else if (e->compl->lex.quo == SIMP)
			get_input_char(e, '\'');

		path = ft_strjoin(e->compl->path, e->compl->poss[0]);
		if (ft_get_file_type(path) == 'd')
			get_input_char(e, '/');
		else if (ft_get_file_type(path) == 'l')
		{
			free(path);
			path = ft_strjoin(e->compl->path, e->compl->cstart);
			if (ft_get_lfile_type(path) == 'd')
				get_input_char(e, '/');
		}
		else
			get_input_char(e, ' ');
		free(path);
	}
	else
	{
		ft_putchar('\n');
		editor_completion_print(e);
		print_prompt(e);
		ft_putstr(e->line);
		int		save;
		save = e->cur;
		e->cur = e->line_len;
		while (e->cur > save)
			move_cursor_left(e);
	}
}

void	editor_completion_print(t_env *e)
{
	int		nb_col;
	int		col_h;
	int		i;
	int		line;

	nb_col = e->ws_col / (e->compl->len_max + 2);
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
				editor_completion_printa(e, i + line);
		}
		ft_putchar('\n');
	}
//	ft_printf("nb_col=%d col_h=%d total=%d\n", nb_col, col_h, e->compl->size);
}

void	editor_completion_printa(t_env *e, int id)
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
