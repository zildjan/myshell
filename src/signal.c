/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/13 19:14:16 by pbourrie          #+#    #+#             */
/*   Updated: 2016/07/19 01:18:23 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	sig_print(int signum)
{
	static int pre = 0;
	static int nb = 0;

	if (pre == signum)
		nb++;
	else
	{
		nb = 0;
		pre = signum;
	}
	if (nb > 100)
		exit(0);
	ft_printf("signal = %ld  (try %ld)  %d\n", signum, nb, getpid());
}

void	catch_signal(void)
{
	signal(SIGINT, sig_mediator);
	signal(SIGQUIT, sig_mediator);
	signal(SIGTSTP, sig_mediator);
	signal(SIGTTIN, sig_mediator);
	signal(SIGTTOU, sig_mediator);
	signal(SIGSEGV, sig_mediator);
	signal(SIGILL, sig_mediator);
	signal(SIGABRT, sig_mediator);
	signal(SIGFPE, sig_mediator);
	signal(SIGBUS, sig_mediator);
	signal(SIGWINCH, sig_mediator);
}

void	signal_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGSEGV, SIG_DFL);
	signal(SIGILL, SIG_DFL);
	signal(SIGABRT, SIG_DFL);
	signal(SIGFPE, SIG_DFL);
	signal(SIGBUS, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
}

void	sig_handler(t_env *e, int signum)
{
	static t_env *se = NULL;

	if (!se && e)
		se = e;
	if (signum == SIGSEGV || signum == SIGABRT
			|| signum == SIGILL || signum == SIGFPE || signum == SIGBUS)
	{
		put_sig_error(signum, "\nEXIT", 2);
		term_restore_backup(NULL);
		exit(1);
	}

//	sig_print(signum);
//	if (se->sub)
//		return ;
//	if (se->sub)
//		ft_printf("SUBME\n");

	if (signum == SIGTTIN)
	{
		tcsetpgrp(1, getpid());
	}
	else if (signum == SIGTTOU)
	{
		tcsetpgrp(0, getpid());
	}
	else if (signum == SIGWINCH)
	{
		refresh_nb_col(se);
	}
}

void	sig_mediator(int signum)
{
	sig_handler(NULL, signum);
}
