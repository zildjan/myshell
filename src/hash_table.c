/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 19:54:39 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/30 20:45:28 by pbourrie         ###   ########.fr       */
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
	int			hash;
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

void	hash_autofill(t_env *e)
{
	int				i;
	struct dirent	*dir_ent;
	void			*dirp;
	char			buf[MAXPATHLEN + 1];
	char			type;

	if (!e->path)
		return ;
	i = -1;
	while (e->path[++i])
		if ((dirp = opendir(e->path[i])) != NULL)
		{
			while ((dir_ent = readdir(dirp)) != NULL)
			{
				ft_bzero(buf, MAXPATHLEN + 1);
				ft_strcpy(buf, e->path[i]);
				ft_strcat(buf, "/");
				ft_strcat(buf, dir_ent->d_name);
				type = ft_get_file_type(buf);
				if (!ft_strequ(dir_ent->d_name, ".") && (type == '-'
					|| type == 'l') && !ft_strequ(dir_ent->d_name, ".."))
					hash_add(e, dir_ent->d_name, buf);
			}
			(void)closedir(dirp);
		}
}
