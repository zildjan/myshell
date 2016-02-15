/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 22:18:13 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/15 02:30:58 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*editor_search(t_env *e)
{
	char	buf[8];
	char	*save;
	char	*search;
	int		num;

	search = ft_strdup("");
	num = 1;
	while (1)
	{
		if (ft_strlen(search))
		{
			char	*tmp;
			tmp = history_find(e, search, num);
			if (tmp)
				save = tmp;
			else
			{
				ft_putchar(7);
				save = ft_strdup(e->line);
			}
		}
		else
			save = ft_strdup(e->line);


		while (e->cur < e->line_len)
			move_cursor_right(e);
		while (e->cur)
			backdelete_input_char(e, 0);

//ft_printf(" line='%s' cur=%d len=%d save='%s'\n", e->line, e->cur, e->line_len, save);

		int		len;
		len = e->prompt_len;
		while (len)
		{
			e->cur++;
			e->line_len++;
			backdelete_input_char(e, 1);
			len--;
		}
		char	*prompt;
		prompt = ft_strdup("(reverse-i-search)`");
		prompt = ft_strdupcat(prompt, search);
		prompt = ft_strdupcat(prompt, "': ");
		gen_prompt(e, prompt);
		free(prompt);
		print_prompt(e);

		get_input_chars(e, save);
		free(save);

		int		i;
		i = e->line_len;
		len = ft_strlen(search);
		while (--i >= 0 && len)
		{
			if (ft_strnequ(e->line + i, search, len))
				break ;
		}
		while (e->cur > i && i >= 0 && len)
			move_cursor_left(e);

		ft_bzero(buf, 8);
		read(0, buf, 7);
		if (ft_strcheck(buf, ft_isprint))
		{
			search = ft_strdupcat(search, buf);
			num = 1;
		}
		else if (buf[0] == 18 && buf[1] == 0)
			num++;
		else if (buf[0] == 127 && buf[1] == 0)
		{
			int		len;
			len = ft_strlen(search);
			if (len > 0)
				search[len - 1] = 0;
			else
				ft_putchar(7);
		}
		else
		{
			save = ft_strdup(e->line);
			while (e->cur < e->line_len)
				move_cursor_right(e);
			while (e->cur)
				backdelete_input_char(e, 0);

			int		len;
			len = e->prompt_len;
			while (len)
			{
				e->cur++;
				e->line_len++;
				backdelete_input_char(e, 1);
				len--;
			}
			if (buf[0] != 3)
				gen_prompt(e, NULL);
			print_prompt(e);

			get_input_chars(e, save);
			int		i;
			i = e->line_len;
			len = ft_strlen(search);
			while (--i >= 0 && len)
			{
				if (ft_strnequ(e->line + i, search, len))
					break ;
			}
			while (e->cur > i && i >= 0 && len)
				move_cursor_left(e);

			free(save);
			free(search);
			return (ft_strdup(buf));
		}
	}
}
