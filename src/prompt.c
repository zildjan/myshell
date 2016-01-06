/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 12:18:49 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 19:37:07 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	print_prompt(t_env *e)
{
	char *spwd;

	spwd = ft_get_up_dir(e->pwd, 1);
//	ft_putstr_fd("{bold}/", 2);
//	ft_putstr_fd(spwd, 2);
//	ft_putstr_fd(" > {rt}", 2);
	ft_printf("{bold}%s > {rt}", spwd);
	e->prompt_len = ft_strlen(spwd) + 3;
	free(spwd);
}

char	*ft_get_up_dir(char *path, int level)
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
	return (ft_strsub(path, i + 1, len));
}
