/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/13 19:14:16 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/11 00:49:44 by pbourrie         ###   ########.fr       */
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
	ft_printf("signal = %ld  (try %ld)\n", signum, nb);
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
//	signal(SIGABRT, sig_mediator);
//	signal(SIGIOT, sig_mediator);

// */
/*
	int	i;
	i = 0;
	while (i < 31)
		signal(i++, sig_print);
// */
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
//		ft_printf("SIGNAL %ld\nEXIT\n", signum);
		term_restore_backup(NULL);
		exit(1);
	}
	else if (signum == SIGTTIN)
	{
		tcsetpgrp(1, getpid());
//		ft_printf("TCSET 1\n");
	}
	else if (signum == SIGTTOU)
	{
		tcsetpgrp(0, getpid());
//		ft_printf("TCSET 2\n");
	}
	else if (signum == SIGWINCH)
	{
		refresh_nb_col(se);
	}
//	else if (signum == SIGIOT)
//	{
//		ft_printf("OU YEAH\n");
//		exit(6);
//	}
//	else
//		ft_printf("signum = %ld\n", signum);
//		ft_printf("signum = %ld\n", signum);
}

void	sig_mediator(int signum)
{
	sig_handler(NULL, signum);
}
