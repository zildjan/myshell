/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 00:43:21 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/15 01:42:19 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*history_find(t_env *e, char *str, int num)
{
	t_histo	*cur;
	int		i;

	i = 1;
	cur = e->histo;
	while (cur)
	{
		if (ft_strstr(cur->line, str))
		{
			if (i == num)
				return (ft_strdup(cur->line));
			else
				i++;
		}
		cur = cur->up;
	}
	return (NULL);
}
