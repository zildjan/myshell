/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 00:43:21 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/16 02:17:22 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*history_find(t_env *e, char *str, int num)
{
	char	*find;

	if (num == 1)
		e->histo_cur = e->histo;
	while (e->histo_cur)
	{
		if (ft_strstr(e->histo_cur->line, str))
		{
			find = (ft_strdup(e->histo_cur->line));
			e->histo_cur = e->histo_cur->up;
			return (find);
		}
		e->histo_cur = e->histo_cur->up;
	}
	return (NULL);
}
