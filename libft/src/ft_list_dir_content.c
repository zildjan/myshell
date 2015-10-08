/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_dir_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/25 20:49:07 by pbourrie          #+#    #+#             */
/*   Updated: 2015/04/24 22:41:02 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"

static char		*get_new_path(char *path, char *current)
{
	char *new_path;

	new_path = ft_strnew(ft_strlen(path) + ft_strlen(current) + 2);
	if (new_path == NULL)
		return (NULL);
	ft_strcpy(new_path, path);
	if (path[0] != 0 && (path[0] != '/' || ft_strlen(path) > 1))
		ft_strcat(new_path, "/");
	ft_strcat(new_path, current);
	return (new_path);
}

static int		get_ent(t_list **list, char *path)
{
	void			*dirp;
	int				i;
	struct dirent	*dir_ent;
	t_list			*tmp;
	t_list			*prev;

	*list = NULL;
	prev = NULL;
	i = 0;
	if ((dirp = opendir(path)) == NULL)
		return (0);
	while ((dir_ent = readdir(dirp)) != NULL)
	{
		tmp = ft_lstnew(&dir_ent->d_name, dir_ent->d_namlen + 1);
		if (prev)
			prev->next = tmp;
		if (*list == NULL)
			*list = tmp;
		prev = tmp;
		i++;
	}
	(void)closedir(dirp);
	return (i);
}

char			**ft_list_dir_content(char *path, char all, char type)
{
	int			i;
	t_list		*list;
	t_list		*prev;
	char		**file_list;
	char		*complete_path;

	if ((i = get_ent(&list, path)) == 0)
		return (0);
	file_list = ft_memalloc(sizeof(char*) * (i + 1));
	i = 0;
	while (list)
	{
		complete_path = get_new_path(path, list->content);
		if ((all || (!ft_is_hidden_file(list->content) && !all))
			&& (!type || type == ft_get_file_type(complete_path)))
			file_list[i++] = ft_strdup(complete_path);
		free(complete_path);
		prev = list;
		free(list->content);
		list = list->next;
		free(prev);
	}
	return (file_list);
}
