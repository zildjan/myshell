/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.h                                          :+:      :+:    :+:   */
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
	while (e->val[i] != NULL)
	{
		if (ft_strnequ(name, e->val[i], len) && e->val[i][len] == '=')
			return (ft_strsub(e->val[i], len + 1, ft_strlen(e->val[i]) - len));
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
	while (e->val[i] != NULL)
	{
		if (ft_strnequ(name, e->val[i], len) && e->val[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
