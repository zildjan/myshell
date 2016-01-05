/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 21:51:04 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	term_init(t_env *e)
{
	e->term_name = get_env_val(e, "TERM");
	e->term_status = 0;
	if (tgetent(NULL, e->term_name) != 1)
		return ;
	if (isatty(0))
	{
		e->term = ft_memalloc(sizeof(struct termios));
		if (tcgetattr(0, e->term) == -1)
		{
			free(e->term);
			e->term = NULL;
			return ;
		}
		else
			term_backup(e);
		term_restore_backup(e->term_back);
		(e->term)->c_lflag &= ~(ICANON);
		(e->term)->c_lflag &= ~(ECHO);
		(e->term)->c_lflag &= ~(ISIG);
		(e->term)->c_cc[VMIN] = 1;
		(e->term)->c_cc[VTIME] = 0;
		tcsetattr(0, TCSADRAIN, e->term);
	}
}

void	term_backup(t_env *e)
{
	size_t	size;

	size = sizeof(struct termios);
	e->term_back = ft_memalloc(size);
	ft_memcpy(e->term_back, e->term, size);
}

void	term_restore(t_env *e)
{
	if (e->term)
	{
		if (e->term_status == 1)
		{
			tcsetattr(0, TCSADRAIN, e->term);
//			ft_printf("RESTORED SHELL %d\n", e->term_status);
		}
		if (e->term_status > 0)
			e->term_status--;
	}
}

void	term_restore_back(t_env *e)
{
	if (!e->term)
		return ;
	if (e->term_status == 0)
	{
		term_restore_backup(NULL);
//		ft_printf("RESTORED BACKUP %d\n", e->term_status);
	}
	e->term_status++;

}

void	term_restore_backup(struct termios *back)
{
	static struct termios *backup;

	if (back)
		backup = back;
	else
	{
		if (backup)
		{
			tcsetattr(0, TCSADRAIN, backup);
		}
	}
}
