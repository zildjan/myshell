/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/14 22:18:13 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/24 17:54:37 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*editor_search(t_env *e)
{
	char	buf[8];
	char	*search;
	int		num;
	char	*saved_prompt;

	saved_prompt = ft_strdup(e->prompt);
	search = ft_strdup("");
	num = 1;
	while (1)
	{
		editor_search_refresh(e, search, num);
		ft_bzero(buf, 8);
		read(0, buf, 7);
		if (!editor_search_key(buf, &search, &num))
		{
			editor_search_exit(e, buf, search, saved_prompt);
			free(saved_prompt);
			return (ft_strdup(buf));
		}
	}
}

void	editor_search_refresh(t_env *e, char *search, int num)
{
	char	*line;
	char	*tmp;

	if (ft_strlen(search))
	{
		tmp = history_find(e, search, num);
		if (tmp)
			line = tmp;
		else
		{
			ft_putchar(7);
			line = ft_strdup(e->line);
		}
	}
	else
		line = ft_strdup(e->line);
	editor_search_print(e, line, search, NULL);
	free(line);
}

int		editor_search_key(char *buf, char **search, int *num)
{
	int		len;

	len = ft_strlen(*search);
	if (ft_strcheck(buf, ft_isprint))
	{
		*search = ft_strdupcat(*search, buf);
		*num = 1;
	}
	else if (buf[0] == 18 && buf[1] == 0 && len)
		*num += 1;
	else if (buf[0] == 127 && buf[1] == 0)
	{
		if (len > 0)
			(*search)[len - 1] = 0;
		else
			ft_putchar(7);
		*num = 1;
	}
	else
		return (0);
	return (1);
}

void	editor_search_exit(t_env *e, char *buf, char *search, char *prom)
{
	char	*line;

	line = ft_strdup(e->line);
	if (buf[0] == 3 && buf[1] == 0)
		editor_search_print(e, line, search, NULL);
	else
		editor_search_print(e, line, search, prom);
	free(line);
	free(search);
}
