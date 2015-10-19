/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/10/09 21:27:14 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*get_env_val(t_env *e, char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (e->var[i] != NULL)
	{
		if (ft_strnequ(name, e->var[i], len) && e->var[i][len] == '=')
			return (ft_strsub(e->var[i], len + 1, ft_strlen(e->var[i]) - len));
		i++;
	}
	return (NULL);
}

int		get_env_id(t_env *e, char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (e->var[i] != NULL)
	{
		if (ft_strnequ(name, e->var[i], len) && e->var[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
