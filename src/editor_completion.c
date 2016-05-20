/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 23:00:22 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/21 01:05:27 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	editor_completion(t_env *e)
{
	completion_update(e);
	if (e->compl->size == 0)
		ft_putchar(7);
	else if (e->compl->mutual[0] != 0)
	{
		editor_completion_complete(e);
		if (e->compl->size == 1)
			editor_completion_complete_end(e);
	}
	if (e->compl->size > 1)
		editor_completion_print(e);
}

void	editor_completion_complete(t_env *e)
{
	char	*to_add;
	char	*escaped;

	to_add = e->compl->mutual + ft_strlen(e->compl->cstart);
	if (e->compl->lex.quo == NONE)
	{
		if (ft_strchr(to_add, '\n'))
		{
			escaped = ft_strdup("'");
			escaped = ft_strdupcat(escaped, to_add);
			escaped = ft_strdupcat(escaped, "'");
		}
		else
			escaped = ft_escape_chars(to_add, " ;|\t><\\&'\"`$!");
	}
	else if (e->compl->lex.quo == DOUB)
		escaped = ft_escape_chars(to_add, "\"\\$");
	else
		escaped = escape_simple_quotes(to_add);
	get_input_chars(e, escaped);
	free(escaped);
}

void	editor_completion_complete_end(t_env *e)
{
	char	*path;
	char	type;

	e->compl->cur = 0;
	path = ft_strjoin(e->compl->path, e->compl->poss[0]);
	type = ft_get_file_type(path);
	if (type == 'd' || (type != 'd' && type != 'l'))
	{
		if (e->compl->lex.quo == DOUB)
			get_input_char(e, '"');
		else if (e->compl->lex.quo == SIMP)
			get_input_char(e, '\'');
	}
	if (type == 'd')
		get_input_char(e, '/');
	else if (type == 'l')
		editor_completion_complete_end_link(e);
	else
		get_input_char(e, ' ');
	free(path);
}

void	editor_completion_complete_end_link(t_env *e)
{
	char	*path;
	char	type;

	path = ft_strjoin(e->compl->path, e->compl->cstart);
	type = ft_get_lfile_type(path);
	if (type == 'd')
		get_input_char(e, '/');
	else if (type != -1)
		get_input_char(e, ' ');
	free(path);
}

char	*escape_simple_quotes(char *str)
{
	int		i;
	int		i2;
	char	*new;

	i = -1;
	i2 = 0;
	while (str[++i])
		if (ft_strchr("'", str[i]))
			i2++;
	new = ft_strnew(i + (i2 * 3));
	i = -1;
	i2 = 0;
	while (str[++i])
	{
		if (ft_strchr("'", str[i]))
		{
			new[i2++] = '\'';
			new[i2++] = '\\';
			new[i2++] = '\'';
		}
		new[i2++] = str[i];
	}
	return (new);
}
