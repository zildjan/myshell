/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/06/30 01:46:54 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	history_load(t_env *e)
{
	char	*line;
	int		ret;
	int		fd;

	e->histo_size = 0;
	if ((fd = open(e->histo_file, O_RDONLY, 0444)) == -1)
		return ;
	while ((ret = get_next_line(fd, &line)))
	{
		if (ft_strlen(line))
			history_add_to_mem(e, line);
		if (line)
			free(line);
		line = NULL;
	}
	if (line)
		free(line);
	close(fd);
}

void	history_init(t_env *e)
{
	if (e->home)
	{
		e->histo_file = ft_strjoin(e->home, "/.42sh_history");
	}
	else
		e->histo_file = NULL;
	history_load(e);
}

void	history_save_ent(t_env *e, char *ent)
{
	int		fd;

	if (!ent)
		return ;
	fd = 0;
	while (ent[fd] && is_aspace(ent[fd]))
		fd++;
	if (fd == (int)ft_strlen(ent))
		return ;
	if (e->histo)
		if (ft_strequ(e->histo->line, ent))
			return ;
	fd = open(e->histo_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd != -1)
	{
		ft_putendl_fd(ent, fd);
		close(fd);
	}
	history_add_to_mem(e, ent);
}

void	history_add_to_mem(t_env *e, char *line)
{
	t_histo	*cur;
	t_histo	*new;

	new = (t_histo*)ft_memalloc(sizeof(t_histo));
	new->line = ft_strdup(line);
	cur = e->histo;
	if (!cur)
	{
		e->histo = new;
		e->histo_begin = new;
		return ;
	}
	new->up = cur;
	cur->down = new;
	e->histo = new;
	e->histo_size++;
}
