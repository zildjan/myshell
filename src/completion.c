/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 22:42:57 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/03 02:05:50 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	completion_update(t_env *e)
{
	char	*start;

	start = completion_get_start(e);
	if (e->compl)
	{
		if (ft_strequ(start, e->compl->start) && start[0])
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
	lexer(e, &e->compl->lex, e->cur);
	ft_printf("a_id=%d quo=%d esc=%d\n", e->compl->lex.a_id, e->compl->lex.quo, e->compl->lex.escape);
	completion_get_poss(e);
}

char	*completion_get_start(t_env *e)
{
	int		start;

	start = 0;
	if (e->cur)
		start = e->cur - 1;
	while (start && !is_aspace(e->line[start]))
		start--;
	if (is_aspace(e->line[start]))
		start++;
	return (ft_strsub(e->line, start, e->cur - start));
}

void	completion_get_poss(t_env *e)
{
	int		len;

	len = ft_strlen(e->compl->start);
	if (!e->compl->lex.a_id && !ft_strchr(e->compl->start, '/'))
	{
		int		i;
		t_hash_b	*tmp;

		i = -1;
		while (++i < e->hash_total)
		{
			tmp = e->hash_t[i];
			while (tmp)
			{
				if (ft_strnequ(e->compl->start, tmp->key, len))
					completion_addtoposs(e, tmp->key);
				tmp = tmp->next;
			}
		}
	}
	else
	{
	char			buf[MAXPATHLEN + 1];
	struct dirent	*dir_ent;
	void			*dirp;

	char	*path;
	char	*start;

	int		pos;

	pos = len;
	if (ft_strchr(e->compl->start, '/'))
	{
		while (pos - 1 && e->compl->start[pos - 1] != '/')
			pos--;
		path = ft_strsub(e->compl->start, 0, pos);
		start = ft_strdup(e->compl->start + pos);
	}
	else
	{
		path = ft_strdup("./");
		start = ft_strdup(e->compl->start);
	}
	ft_printf("path='%s'  start='%s' pos=%d\n", path, start, pos);
	len = ft_strlen(start);
	
		if ((dirp = opendir(path)) != NULL)
		{
			while ((dir_ent = readdir(dirp)) != NULL)
			{
				ft_bzero(buf, MAXPATHLEN + 1);
				ft_strcpy(buf, path);
				ft_strcat(buf, "");
				ft_strcat(buf, dir_ent->d_name);

//				ft_printf("path='%s'  start='%s'\n", dir_ent->d_name, start);
				if (ft_strnequ(start, dir_ent->d_name, len))
					if ((!ft_strequ(dir_ent->d_name, ".")
						&& !ft_strequ(dir_ent->d_name, "..")
						&& start[0] != '.') || start[0] == '.')
					{
						if ((!e->compl->lex.a_id && !access(buf, X_OK))
							|| e->compl->lex.a_id)
							completion_addtoposs(e, dir_ent->d_name);

					}
			}
			(void)closedir(dirp);
		}
		free(path);
		free(start);
	}
}

void	completion_addtoposs(t_env *e, char *str)
{
	int		old_s;
	int		new_s;

	if (ft_get_file_type(str) == 'd')
		e->compl->poss[e->compl->size++] = ft_strjoin(str, "/");
	else
		e->compl->poss[e->compl->size++] = ft_strdup(str);
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
	free(e->compl);
	e->compl = NULL;
}
