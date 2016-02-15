/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_get_poss.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 00:40:33 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/14 21:54:43 by pbourrie         ###   ########.fr       */
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

void	completion_get_file_poss(t_env *e, char *path)
{
	t_dirent	*dir_ent;
	void		*dirp;
	char		*tmp;

	if (path[0] != '/')
	{
		tmp = ft_strjoin(e->pwd, "/");
		tmp = ft_strdupcat(tmp, path);
		free(path);
		path = tmp;
	}
	builtin_cd_clean_path(path, 0);
	path = ft_strdupcat(path, "/");
	if ((dirp = opendir(path)) != NULL)
	{
		while ((dir_ent = readdir(dirp)) != NULL)
			completion_add_dirent(e, dir_ent, path);
		(void)closedir(dirp);
	}
	e->compl->path = path;
}

void	completion_add_dirent(t_env *e, t_dirent *file, char *path)
{
	char	buf[MAXPATHLEN + 1];
	char	*cstart;
	int		len;

	cstart = e->compl->cstart;
	len = ft_strlen(cstart);
	ft_bzero(buf, MAXPATHLEN + 1);
	ft_strcpy(buf, path);
	ft_strcat(buf, "/");
	ft_strcat(buf, file->d_name);
	if (ft_strnequ(cstart, file->d_name, len))
		if ((!ft_strequ(file->d_name, ".")
			&& !ft_strequ(file->d_name, "..")) || cstart[0] == '.')
			if (e->compl->lex.a_id
				|| (!e->compl->lex.a_id && !access(buf, X_OK)))
				completion_addtoposs(e, file->d_name);
}
