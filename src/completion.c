/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 22:42:57 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/04 01:33:35 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	completion_update(t_env *e)
{
	char	*start;
	t_lex	lex;

	lexer(e, &lex, e->cur);
//	ft_printf("i=%d\n", lex.i);
	start = ft_strsub(e->line, e->cur - lex.ib, lex.ib);
	if (e->compl)
	{
		if (ft_strequ(start, e->compl->start) && lex.ib && lex.i == e->compl->lex.i)
		{
			free(start);
			return ;
		}
	}
	completion_free(e);
	e->compl = (t_compl*)ft_memalloc(sizeof(t_compl));
	e->compl->total = 3;
	e->compl->poss = (char**)ft_memalloc(sizeof(char*) * e->compl->total);
	e->compl->start = start;
	e->compl->cur = -1;
	e->compl->lex = lex;
//	ft_printf("\na_id=%d quo=%d esc=%d ", e->compl->lex.a_id, e->compl->lex.quo, e->compl->lex.escape);
//	ft_printf("ib=%d i=%d \nstart='%s'\n", e->compl->lex.ib, lex.i , start);
	completion_get_poss(e);
	myqsort(e->compl->poss, 0, e->compl->size - 1);
}

void	completion_get_poss(t_env *e)
{
	int		len;

	len = ft_strlen(e->compl->start);
	if (len >= 1 && e->compl->start[0] == '$')
	{
		completion_get_var_poss(e, len);
	}
	else if (!e->compl->lex.a_id && !ft_strchr(e->compl->start, '/'))
	{
		completion_get_cmd_poss(e, len);
	}
	else
	{
		completion_get_file_poss(e, len);
	}
}

void	completion_get_cmd_poss(t_env *e, int len)
{
	int				i;
	struct dirent	*dir_ent;
	void			*dirp;

	e->compl->cstart = ft_strdup(e->compl->start);
	i = -1;
	while (e->builtin_list[++i])
		if (ft_strnequ(e->compl->start, e->builtin_list[i], len))
			completion_addtoposs(e, e->builtin_list[i]);
	if (!e->path)
		return ;
	i = -1;
	while (e->path[++i])
	{
		if ((dirp = opendir(e->path[i])) != NULL)
		{
			while ((dir_ent = readdir(dirp)) != NULL)
				completion_add_dirent(e, dir_ent, e->path[i]);
			(void)closedir(dirp);
		}
	}
}

void	completion_get_file_poss(t_env *e, int len)
{
	t_dirent	*dir_ent;
	void		*dirp;
	char		*path;
	int			pos;

	pos = len;
	if (ft_strchr(e->compl->start, '/'))
	{
		while (pos - 1 && e->compl->start[pos - 1] != '/')
			pos--;
		path = ft_strsub(e->compl->start, 0, pos);
		e->compl->cstart = ft_strdup(e->compl->start + pos);
	}
	else
	{
		path = ft_strdup("./");
		e->compl->cstart = ft_strdup(e->compl->start);
	}
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

void	completion_addtoposs(t_env *e, char *str)
{
	int		old_s;
	int		new_s;
	int		i;

	i = -1;
	while (e->compl->poss[++i])
		if (ft_strequ(str, e->compl->poss[i]))
			return ;
	e->compl->poss[e->compl->size++] = ft_strdup(str);
	i = ft_strlen(str);
	if (i > e->compl->len_max)
		e->compl->len_max = i;
	if (e->compl->size + 10 > e->compl->total)
	{
		old_s = sizeof(char*) * e->compl->total;
		e->compl->total += 100;
		new_s = sizeof(char*) * e->compl->total;
		e->compl->poss = (char**)ft_memrealloc(e->compl->poss, old_s, new_s);
	}
	e->compl->poss[e->compl->size] = NULL;
}

void	completion_free(t_env *e)
{
	int		i;

	if (!e->compl)
		return ;
	i = -1;
	while (e->compl->poss[++i])
		free(e->compl->poss[i]);
	free(e->compl->poss);
	free(e->compl->start);
	if (e->compl->cstart)
		free(e->compl->cstart);
	if (e->compl->path)
		free(e->compl->path);
	free(e->compl);
	e->compl = NULL;
}
