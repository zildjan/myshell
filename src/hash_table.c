/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 19:54:39 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/28 01:19:30 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		hash1(char *name, int size)
{
	int accum;
	int len;

	if (size <= 0)
		return (0);
	len = ft_strlen(name);
	accum = 0;
	while (len > 0)
	{
		accum <<= 1;
		accum += (unsigned)(*name++ ^ 0xFF);
		len--;
	}
	if (accum < 0)
		accum = 0;
	return (accum % size);
}

char	*hash_find(t_env *e, char *key)
{
	int				hash;
	t_hash_b	*bucket;

	hash = hash1(key, e->hash_total);
	bucket = e->hash_t[hash];
	while (bucket)
	{
		if (ft_strequ(key, bucket->key))
			return (bucket->val);
		bucket = bucket->next;
	}
	return (NULL);
}

char	*hash_add_cmd(t_env *e, char *cmd)
{
	int		i;
	char	cmd_path[MAXPATHLEN + 1];
	char	type;

	i = 0;
	while (e->path[i])
	{
		ft_bzero(cmd_path, MAXPATHLEN + 1);
		ft_strcpy(cmd_path, e->path[i]);
		ft_strcat(cmd_path, "/");
		ft_strcat(cmd_path, cmd);
		type = ft_get_file_type(cmd_path);
		if (!access(cmd_path, X_OK) && (type == '-' || type == 'l'))
			return (hash_add(e, cmd, cmd_path));
		i++;
	}
	return (NULL);
}

char	*hash_add(t_env *e, char *key, char *val)
{
	int			hash;
	t_hash_b	*tmp;
	t_hash_b	*new;

	if (hash_find(e, key))
		return (NULL);
	hash_table_resize(e);
	e->hash_size++;
	hash = hash1(key, e->hash_total);
	new = (t_hash_b*)ft_memalloc(sizeof(t_hash_b));
	new->val = ft_strdup(val);
	new->key = ft_strdup(key);
	tmp = e->hash_t[hash];
	if (!tmp)
	{
		e->hash_t[hash] = new;
		return (new->val);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (new->val);
}

void	hash_table_resize(t_env *e)
{
	t_hash_b	**old_table;
	int			old_total;

	if (e->hash_size * 2 < e->hash_total)
		return ;
	old_total = e->hash_total;
	e->hash_total = (e->hash_size * 2) + 263;
	old_table = e->hash_t;
	e->hash_size = 0;
	e->hash_t = (t_hash_b**)ft_memalloc(sizeof(t_hash_b*) * e->hash_total);
	hash_table_rebuilt(e, old_table, old_total);
}

void	hash_table_rebuilt(t_env *e, t_hash_b **old_table, int old_total)
{
	int				i;
	t_hash_b	*cur;
	t_hash_b	*tmp;

	i = -1;
	while (++i < old_total)
	{
		cur = old_table[i];
		while (cur)
		{
			hash_add(e, cur->key, cur->val);
			tmp = cur;
			cur = cur->next;
			free(tmp->key);
			free(tmp->val);
			free(tmp);
		}
	}
	free(old_table);
}

void	hash_autofill(t_env *e)
{
	int				i;
	struct dirent	*dir_ent;
	void			*dirp;
	char			buf[MAXPATHLEN + 1];

	if (!e->path)
		return ;
	i = -1;
	while (e->path[++i])
	{
		if ((dirp = opendir(e->path[i])) != NULL)
		{
			while ((dir_ent = readdir(dirp)) != NULL)
			{
					ft_bzero(buf, MAXPATHLEN + 1);
					ft_strcpy(buf, e->path[i]);
					ft_strcat(buf, "/");
					ft_strcat(buf, dir_ent->d_name);
					if (!access(buf, X_OK) && (ft_get_file_type(buf) == '-'
						|| ft_get_file_type(buf) == 'l'))
						hash_add(e, dir_ent->d_name, buf);
			}
			(void)closedir(dirp);
		}
	}
}
