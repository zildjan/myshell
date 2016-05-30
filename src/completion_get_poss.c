/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_get_poss.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 00:40:33 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/30 19:51:29 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	completion_get_poss(t_env *e)
{
	int		len;
	char	*path;

	len = ft_strlen(e->compl->start);
	if (len >= 1 && e->compl->start[0] == '$')
		completion_get_var_poss(e, len);
	else if (!e->compl->lex.a_id && !ft_strchr(e->compl->start, '/'))
		completion_get_cmd_poss(e, len);
	else
	{
		if (ft_strchr(e->compl->start, '/'))
		{
			while (len - 1 && e->compl->start[len - 1] != '/')
				len--;
			path = ft_strsub(e->compl->start, 0, len);
			e->compl->cstart = ft_strdup(e->compl->start + len);
		}
		else
		{
			path = ft_strdup("./");
			e->compl->cstart = ft_strdup(e->compl->start);
		}
		completion_get_file_poss(e, path);
	}
}

void	completion_get_var_poss(t_env *e, int len)
{
	int		i;
	int		i2;
	char	*var;

	e->compl->cstart = ft_strdup(e->compl->start);
	if (!e->var)
		return ;
	i = -1;
	while (e->var[++i])
		if (ft_strnequ(e->compl->start + 1, e->var[i], len - 1))
		{
			var = ft_strjoin("$", e->var[i]);
			i2 = 0;
			while (var[i2] && var[i2] != '=')
				i2++;
			var[i2] = 0;
			completion_addtoposs(e, var);
			free(var);
		}
}

void	completion_get_cmd_poss(t_env *e, int len)
{
	int				i;
	struct dirent	*dir_ent;
	void			*dirp;

	e->compl->cstart = ft_strdup(e->compl->start);
	if (ft_strequ(".", e->compl->cstart))
	{
		completion_addtoposs(e, ".");
		return ;
	}
	i = -1;
	while (e->builtin_list[++i])
		if (ft_strnequ(e->compl->start, e->builtin_list[i], len))
			completion_addtoposs(e, e->builtin_list[i]);
	completion_get_alias_poss(e, len);
	if (!e->path)
		return ;
	i = -1;
	while (e->path[++i])
		if ((dirp = opendir(e->path[i])) != NULL)
		{
			while ((dir_ent = readdir(dirp)) != NULL)
				completion_add_dirent(e, dir_ent, e->path[i]);
			(void)closedir(dirp);
		}
}

void	completion_get_alias_poss(t_env *e, int len)
{
	t_alias			*alias;

	alias = e->alias;
	while (alias)
	{
		if (ft_strnequ(e->compl->start, alias->key, len))
			completion_addtoposs(e, alias->key);
		alias = alias->next;
	}
}
