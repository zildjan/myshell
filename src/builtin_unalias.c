/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unalias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 22:09:09 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/29 00:07:10 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	builtin_unalias(t_env *e)
{
	int		i;

	if (e->carg[1] == NULL)
	{
		i = e->cmd[e->cid].fd_err;
		ft_putendl_fd("21sh: unalias: usage: [-a] name [name ...]", i);
		e->status = 2;
	}
	else if (ft_strequ(e->carg[1], "-a"))
		free_alias(e);
	else
	{
		i = 0;
		while (e->carg[++i])
		{
			builtin_unalias_remove(e, e->carg[i]);
		}
	}
}

void	builtin_unalias_remove(t_env *e, char *name)
{
	t_alias	*alias;
	t_alias	*pre;

	pre = NULL;
	alias = e->alias;
	while (alias)
	{
		if (ft_strequ(alias->key, name))
		{
			if (pre)
				pre->next = alias->next;
			else
				e->alias = alias->next;
			free(alias->val);
			free(alias->key);
			free(alias);
			return ;
		}
		pre = alias;
		alias = alias->next;
	}
	ft_putstr_fd("21sh: unalias: ", e->cmd[e->cid].fd_err);
	ft_putstr_fd(name, e->cmd[e->cid].fd_err);
	ft_putendl_fd(": not found.", e->cmd[e->cid].fd_err);
}
