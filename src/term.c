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
		term_restore(e->term_back);
		(e->term)->c_lflag &= ~(ICANON);
		(e->term)->c_lflag &= ~(ECHO);
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

void	term_restore(struct termios *back)
{
	static struct termios *backup;

	if (back)
		backup = back;
	else
	{
		tcsetattr(0, TCSADRAIN, backup);
//		ft_printf("RESTORED\n");
	}
}
