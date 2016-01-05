/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 21:51:04 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	history_load(t_env *e)
{
	char	*line;
	int		ret;
	int		fd;

	e->histo_size = 0;
	e->histo_line = NULL;
	if ((fd = open(e->histo_file, O_RDONLY , 0444)) == -1)
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
		e->histo_file = ft_strjoin(e->home, "/.21sh_history");
	}
	else
		e->histo_file = NULL;
	history_load(e);
}

void	history_add(t_env *e, char escape)
{
	int		len;

	e->histo_line = ft_strdupcat(e->histo_line, e->line);
	if (e->histo_line && escape)
	{
		len = ft_strlen(e->histo_line);
		if (e->histo_line[len - 1] == '\\')
			e->histo_line[len - 1] = 0;
	}
}

void	history_save_ent(t_env *e)
{
	int		fd;

	if (!e->histo_line)
		return ;
	if (e->histo)
		if (ft_strequ(e->histo->line, e->histo_line))
		{
			if (e->histo_line)
				free(e->histo_line);
			e->histo_line = NULL;
			return ;
		}
	fd = open(e->histo_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd != -1)
	{
		ft_putendl_fd(e->histo_line, fd);
		close(fd);
	}
	history_add_to_mem(e, e->histo_line);
	if (e->histo_line)
		free(e->histo_line);
	e->histo_line = NULL;
}

void	history_add_to_mem(t_env *e, char *line)
{
	t_histo	*cur;
	t_histo	*new;

//	ft_printf("->'%s' \n", line);
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

void	history_print(t_env *e)
{
	t_histo	*cur;
	int		i;
	int		fd;

	i = 1;
	fd = e->cmd[e->cid].fd_out;
	cur = e->histo_begin;
	while (cur)
	{
		ft_putnchar_fd((ft_nbrlen(e->histo_size) - ft_nbrlen(i)) + 1, ' ', fd);

		ft_putnbr_fd(i, fd);
		ft_putstr_fd("  ", fd);
		ft_putendl_fd(cur->line, fd);
		cur = cur->down;
		i++;
	}
}
