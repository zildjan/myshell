/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_get_file_poss.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 19:49:54 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/30 19:50:16 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

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
	char	type;

	cstart = e->compl->cstart;
	len = ft_strlen(cstart);
	ft_bzero(buf, MAXPATHLEN + 1);
	ft_strcpy(buf, path);
	ft_strcat(buf, "/");
	ft_strcat(buf, file->d_name);
	type = ft_get_file_type(buf);
	if (ft_strnequ(cstart, file->d_name, len))
		if ((!ft_strequ(file->d_name, ".")
			&& !ft_strequ(file->d_name, "..")) || cstart[0] == '.')
			if (e->compl->lex.a_id
				|| (!e->compl->lex.a_id && (!access(buf, X_OK)
											|| type == 'd')))
				completion_addtoposs(e, file->d_name);
}
