/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/10/09 21:27:14 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	set_new_env_var(t_env *e, char *name, char *val)
{
	int		i;
	char	*temp;

	i = 0;
	while (e->var[i] != NULL)
		i++;
	temp = ft_strjoin(name, "=");
	e->var[i] = ft_strjoin(temp, val);
	e->var[i + 1] = NULL;
	free(temp);
}

void	set_env_var(t_env *e, char *name, char *val)
{
	int		i;
	char	*temp;

	i = get_env_id(e, name);
	if (i == -1)
		set_new_env_var(e, name, val);
	else
	{
		free(e->var[i]);
		temp = ft_strjoin(name, "=");
		e->var[i] = ft_strjoin(temp, val);
		free(temp);
	}
}

int		unset_env_var(t_env *e, char *name)
{
	int		i;

	i = get_env_id(e, name);
	if (i == -1)
		return (0);
	free(e->var[i]);
	i++;
	while (e->var[i] != NULL)
	{
		e->var[i - 1] = e->var[i];
		i++;
	}
	e->var[i - 1] = NULL;
	return (1);
}
