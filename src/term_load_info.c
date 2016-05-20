/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_load_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/10 00:23:28 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/20 23:31:53 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	term_load_info(t_env *e)
{
	e->t.mi = tgetflag("mi");
	e->t.eo = tgetflag("eo");
	e->t.xn = tgetflag("xn");
	e->t.tab_len = 8;
	e->t.tab_len = tgetnum("it");
	term_load_key_default(e);
	term_load_key(e);
//	ft_printf("mi=%d eo=%d xn=%d ", e->t.mi, e->t.eo, e->t.xn);
//	ft_printf("km=%d\n", tgetflag("km"));
}

void	term_load_key_default(t_env *e)
{
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
	term_load_key_default2(e);
}

void	term_load_key_default2(t_env *e)
{
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
}

void	term_load_key(t_env *e)
{
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
	term_load_key2(e);
}

void	term_load_key2(t_env *e)
{
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
