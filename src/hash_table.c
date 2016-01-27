/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 19:54:39 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/27 02:08:51 by pbourrie         ###   ########.fr       */
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
		accum += (unsigned) (*name++ ^ 0xFF);
		len--;
	}
	if (accum < 0)
		accum = 0;
//	return 2;
	return (accum % size);
}


void	hash_table_print(t_env *e)
{
	int				i;
	int				total;
	int				col;
	int				nb;
	t_hash_bucket	*tmp;

	total = 0;
	col = 0;
	i = -1;
	while (++i < e->hash_total)
	{
		tmp = e->hash_t[i];
		nb = 0;
		while (tmp)
		{
			ft_putnbr_fd(total, e->cmd[e->cid].fd_out);
			ft_putstr_fd("  ", e->cmd[e->cid].fd_out);
			ft_putnbr_fd(i, e->cmd[e->cid].fd_out);
			ft_putstr_fd("  ", e->cmd[e->cid].fd_out);
			ft_putstr_fd(tmp->key, e->cmd[e->cid].fd_out);
			ft_putstr_fd(" -> ", e->cmd[e->cid].fd_out);
			ft_putendl_fd(tmp->val, e->cmd[e->cid].fd_out);
			tmp = tmp->next;
			if (nb > col)
				col = nb;
			nb++;
			total++;
		}
	}
	ft_printf("Size=%d Total=%d Col=%d\n", e->hash_size, e->hash_total, col);
}

char	*hash_find(t_env *e, char *key)
{
	int				hash;
	t_hash_bucket	*bucket;

	hash = hash1(key, e->hash_total);
	bucket = e->hash_t[hash];
	while (bucket)
	{
//		ft_printf("ICI %s\n", bucket->val);
		if (ft_strequ(key, bucket->key))
		{
//			ft_printf("ICI\n");
			return (bucket->val);
		}
		bucket = bucket->next;
	}
//	ft_printf("NOT FOUND\n");
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
		if (ft_get_file_mode(cmd_path) % 2 == 1 && (type == '-' || type == 'l'))
		{
//			ft_printf("NEW %s -> %s\n", cmd, cmd_path);
			return (hash_add(e, cmd, cmd_path));
		}
		i++;
	}
	return (NULL);
}

char	*hash_add(t_env *e, char *key, char *val)
{
	int				hash;
	t_hash_bucket	*tmp;
	t_hash_bucket	*new;

	if (hash_find(e, key))
		return (NULL);
	hash_table_resize(e);
	e->hash_size++;
	hash = hash1(key, e->hash_total);
	new = (t_hash_bucket*)ft_memalloc(sizeof(t_hash_bucket));
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
	t_hash_bucket	**old_table;
	int				old_total;

	if (e->hash_size * 2 < e->hash_total)
		return ;
	old_total = e->hash_total;
	e->hash_total = (e->hash_size * 2) + 167;
	old_table = e->hash_t;
	e->hash_size = 0;
	e->hash_t = (t_hash_bucket**)ft_memalloc(sizeof(t_hash_bucket*) * e->hash_total);

//	ft_printf("RESIZE %d->%d\n", old_total, e->hash_total);

	int				i;
	t_hash_bucket	*cur;
	t_hash_bucket	*tmp;

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
//	usleep(70000);
}


void	hash_fill(t_env *e)
{
	int				i;
	int				total;
	struct dirent	*dir_ent;
	void			*dirp;
	char			buf[MAXPATHLEN + 1];

	char	*tabc;
	tabc = (char*)ft_memalloc(sizeof(char) * 5000);

	total = 0;
	i = -1;
	while (e->path[++i])
	{
//		ft_printf("->%s\n", e->path[i]);
		if ((dirp = opendir(e->path[i])) != NULL)
		{

			while ((dir_ent = readdir(dirp)) != NULL)
			{
				if (!ft_strequ(dir_ent->d_name, "..") && !ft_strequ(dir_ent->d_name, "."))
				{
					ft_bzero(buf, MAXPATHLEN + 1);
					ft_strcpy(buf, e->path[i]);
					ft_strcat(buf, "/");
					ft_strcat(buf, dir_ent->d_name);

					if ((ft_get_file_mode(buf) % 100) % 2 == 1
						&& (ft_get_file_type(buf) == '-' || ft_get_file_type(buf) == 'l'))
					{
						if (tabc[hash1(dir_ent->d_name, 5000)] == 0)
							tabc[hash1(dir_ent->d_name, 5000)] = 1;
						else
						{
							tabc[hash1(dir_ent->d_name, 5000)]++;
//							ft_printf("%5d %d %20s", total, tabc[hash(dir_ent->d_name, 5000)], buf);
//							ft_printf(" = '%d'\n", hash(dir_ent->d_name, 5000));
							total++;
						}
//						usleep(1000);
						ft_printf("%d %s\n", ft_get_file_mode(buf), dir_ent->d_name);
						hash_add(e, dir_ent->d_name, buf);
					}
//					else
//						ft_printf("ERREUR %c %d %s\n", ft_get_file_type(buf), ft_get_file_mode(buf), buf);
				}
			}
			(void)closedir(dirp);
		}
	}
	free(tabc);
}
// */
