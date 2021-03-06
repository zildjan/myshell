/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 21:58:29 by pbourrie          #+#    #+#             */
/*   Updated: 2016/07/25 00:11:09 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	builtin_alias(t_env *e)
{
	int		i;

	e->status = 0;
	if (e->carg[1] == NULL)
		builtin_alias_print(e, NULL);
	else
	{
		i = 0;
		while (e->carg[++i])
		{
			if (ft_strchr(e->carg[i], '='))
				builtin_alias_add_check(e, e->carg[i]);
			else
				builtin_alias_print(e, e->carg[i]);
		}
	}
}

void	builtin_alias_add_check(t_env *e, char *str)
{
	char	*key;
	char	*val;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = ft_strndup(str, i++);
	val = ft_strdup(str + i);
	if (builtin_setenv_check(key, 0, 1))
	{
		ft_putendl_fd("42sh: alias: invalid name.", e->cmd[e->cid].fd_err);
		e->status = 1;
	}
	else if (builtin_setenv_check(val, 0, 0))
	{
		ft_putendl_fd("42sh: alias: Bad character.", e->cmd[e->cid].fd_err);
		e->status = 1;
	}
	else
		builtin_alias_add(e, key, val);
}

void	builtin_alias_add(t_env *e, char *key, char *val)
{
	t_alias	*alias;
	t_alias	*new;

	alias = e->alias;
	while (alias)
	{
		if (ft_strequ(alias->key, key))
		{
			free(alias->val);
			free(key);
			alias->val = val;
			return ;
		}
		alias = alias->next;
	}
	new = (t_alias*)ft_memalloc(sizeof(t_alias));
	new->key = key;
	new->val = val;
	new->used = 0;
	new->next = NULL;
	if (e->alias)
		new->next = e->alias;
	e->alias = new;
}

void	builtin_alias_print(t_env *e, char *key)
{
	t_alias	*alias;

	alias = e->alias;
	while (alias)
	{
		if (ft_strequ(alias->key, key) || !key)
		{
			ft_putstr_fd("alias ", e->cmd[e->cid].fd_out);
			ft_putstr_fd(alias->key, e->cmd[e->cid].fd_out);
			ft_putstr_fd("='", e->cmd[e->cid].fd_out);
			ft_putstr_fd(alias->val, e->cmd[e->cid].fd_out);
			ft_putstr_fd("'\n", e->cmd[e->cid].fd_out);
			if (key)
				return ;
		}
		alias = alias->next;
	}
	if (key)
	{
		e->status = 1;
		ft_putstr_fd("42sh: alias: ", e->cmd[e->cid].fd_err);
		ft_putstr_fd(key, e->cmd[e->cid].fd_err);
		ft_putendl_fd(": not found.", e->cmd[e->cid].fd_err);
	}
}
