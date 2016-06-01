/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 12:18:49 by pbourrie          #+#    #+#             */
/*   Updated: 2016/06/01 19:23:32 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	print_prompt(t_env *e)
{
	if (!e->prompt)
		gen_prompt(e, NULL);
	ft_putstr_fd(e->prompt, 2);
}

void	gen_prompt(t_env *e, char *str)
{
	char	*tmp;

	if (e->prompt)
		free(e->prompt);
	if (!str)
	{
		e->prompt = ft_strdup("\033[1m");
		tmp = ft_get_dir_up(e->pwd, 1);
		e->prompt_len = ft_strlen(tmp) + 3;
		e->prompt = ft_strdupcat(e->prompt, tmp);
		free(tmp);
		e->prompt = ft_strdupcat(e->prompt, " > \033[0m");
	}
	else
	{
		e->prompt = ft_strdup(str);
		e->prompt_len = ft_strlen(e->prompt);
	}
}

char	*ft_get_dir_up(char *path, int level)
{
	int	i;
	int	len;

	if (!path)
		return (NULL);
	len = 0;
	i = ft_strlen(path);
	while (i >= 0)
	{
		if (path[i] == '/' && !level)
			break ;
		else if (path[i] == '/')
			level--;
		len++;
		i--;
	}
	if (i == 0)
		i--;
	return (ft_strsub(path, i + 1, len));
}
