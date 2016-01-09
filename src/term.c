/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 19:55:32 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/09 01:37:14 by pbourrie         ###   ########.fr       */
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
//		ft_printf("mi=%d eo=%d xn=%d", tgetflag("mi"), tgetflag("eo"), tgetflag("xn"));
//		ft_printf(" NP=%d\n", tgetflag("NP"));
		term_load(e);
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

void	term_load(t_env *e)
{
	e->t.mi = tgetflag("mi");
	e->t.eo = tgetflag("eo");
	e->t.xn = tgetflag("xn");

	e->t.kl[0] = 27;
	e->t.kl[1] = 91;
	e->t.kl[2] = 68;
	e->t.kr[0] = 27;
	e->t.kr[1] = 91;
	e->t.kr[2] = 67;
	e->t.ku[0] = 27;
	e->t.ku[1] = 91;
	e->t.ku[2] = 65;
	e->t.kd[0] = 27;
	e->t.kd[1] = 91;
	e->t.kd[2] = 66;
	e->t.kh[0] = 27;
	e->t.kh[1] = 91;
	e->t.kh[2] = 72;
	e->t.ke[0] = 27;
	e->t.ke[1] = 91;
	e->t.ke[2] = 70;
	e->t.kh_s[0] = 27;
	e->t.kh_s[1] = 91;
	e->t.kh_s[2] = 49;
	e->t.kh_s[3] = 59;
	e->t.kh_s[4] = 50;
	e->t.kh_s[5] = 72;
	e->t.ke_s[0] = 27;
	e->t.ke_s[1] = 91;
	e->t.ke_s[2] = 49;
	e->t.ke_s[3] = 59;
	e->t.ke_s[4] = 50;
	e->t.ke_s[5] = 70;
	e->t.kl_s[0] = 27;
	e->t.kl_s[1] = 91;
	e->t.kl_s[2] = 49;
	e->t.kl_s[3] = 59;
	e->t.kl_s[4] = 50;
	e->t.kl_s[5] = 68;
	e->t.kr_s[0] = 27;
	e->t.kr_s[1] = 91;
	e->t.kr_s[2] = 49;
	e->t.kr_s[3] = 59;
	e->t.kr_s[4] = 50;
	e->t.kr_s[5] = 67;
	e->t.ksup[0] = 27;
	e->t.ksup[1] = 91;
	e->t.ksup[2] = 51;
	e->t.ksup[3] = 126;

	if (tgetstr("kl", NULL))
		ft_strcpy(e->t.kl, tgetstr("kl", NULL));
	if (tgetstr("kr", NULL))
		ft_strcpy(e->t.kr, tgetstr("kr", NULL));
	if (tgetstr("ku", NULL))
		ft_strcpy(e->t.ku, tgetstr("ku", NULL));
	if (tgetstr("kd", NULL))
		ft_strcpy(e->t.kd, tgetstr("kd", NULL));
	if (tgetstr("#2", NULL))
		ft_strcpy(e->t.kh_s, tgetstr("#2", NULL));
	if (tgetstr("*7", NULL))
		ft_strcpy(e->t.ke_s, tgetstr("*7", NULL));
	if (tgetstr("kh", NULL))
		ft_strcpy(e->t.kh, tgetstr("kh", NULL));
	if (tgetstr("@7", NULL))
		ft_strcpy(e->t.ke, tgetstr("@7", NULL));
	if (tgetstr("%i", NULL))
		ft_strcpy(e->t.kr_s, tgetstr("%i", NULL));
	if (tgetstr("#4", NULL))
		ft_strcpy(e->t.kl_s, tgetstr("#4", NULL));
	if (tgetstr("kD", NULL))
		ft_strcpy(e->t.ksup, tgetstr("kD", NULL));

	if (e->t.kr[1] == 91)
		e->t.kr[1] = 79;
	if (e->t.kl[1] == 91)
		e->t.kl[1] = 79;
	if (e->t.ku[1] == 91)
		e->t.ku[1] = 79;
	if (e->t.kd[1] == 91)
		e->t.kd[1] = 79;
	if (e->t.kr_s[1] == 91)
		e->t.kr_s[1] = 79;
	if (e->t.kl_s[1] == 91)
		e->t.kl_s[1] = 79;
	if (e->t.kh[1] == 91)
		e->t.kh[1] = 79;
	if (e->t.ke[1] == 91)
		e->t.ke[1] = 79;
	if (e->t.ksup[1] == 91)
		e->t.ksup[1] = 79;
	if (e->t.kh_s[1] == 91)
		e->t.kh_s[1] = 79;
	if (e->t.ke_s[1] == 91)
		e->t.ke_s[1] = 79;
}

