/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/05 01:59:35 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	term_init(t_env *e)
{
	e->term_name = get_env_val(e, "TERM");
	e->term_status = 0;
	if (tgetent(NULL, e->term_name) != 1)
		return ;
	if (isatty(e->fd_in) && isatty(1) && isatty(2))
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
		term_load_info(e);
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
	int				try;
//	struct termios	*test;

//	test = NULL;
//	test = ft_memalloc(sizeof(struct termios));
	if (e->term)
	{
		if (e->term_status == 1)
		{
//			ft_printf("\nRESTAURE III\n");
//			ft_putchar(7);
			refresh_nb_col(e);
			try = 0;
			while (tcsetattr(0, TCSADRAIN, e->term) == -1 && try < 100)
				try++;
/*			tcsetattr(0, TCSADRAIN, e->term);
			tcgetattr(0, test);
			while (ft_memcmp(test, e->term, sizeof(struct termios)) && try < 100)
			{
				ft_printf("diff=%d\n", ft_memcmp(test, e->term, sizeof(struct termios)));
//				ft_printf("ICI\n");
				tcsetattr(0, TCSADRAIN, e->term);
				tcgetattr(0, test);
				usleep(10);
				try++;
			}
			if (try > 3)
			ft_printf("TRY=%d\n", try);*/
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
//			ft_printf("\nINSTAURE  000\n");
	}
	e->term_status++;
}

void	term_restore_backup(struct termios *back)
{
	static struct termios	*backup;
	int						try;

	if (back)
		backup = back;
	else
	{
		if (backup)
		{
			try = 0;
			while (tcsetattr(0, TCSADRAIN, backup) == -1 && try < 20)
				try++;
		}
	}
}
