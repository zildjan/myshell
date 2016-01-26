/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 12:18:49 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/25 17:42:40 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	print_prompt(t_env *e)
{
	char *spwd;

	spwd = ft_get_dir_up(e->pwd, 1);
	ft_printf("{bold}%s > {rt}", spwd);
	e->prompt_len = ft_strlen(spwd) + 3;
	free(spwd);
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
