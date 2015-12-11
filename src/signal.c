/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/13 19:14:16 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 20:37:19 by pbourrie         ###   ########.fr       */
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
	if (signum == SIGINT)
	{
		print_prompt(se);
	}
	else if (signum == SIGTSTP)
	{		
//		ft_printf("STOP %ld\n", se->jobs->pid);
//		if (se->jobs && se->jobs->pid)
//			kill(se->jobs->pid, SIGTSTP);
	}
	else if (signum == SIGTTIN)
		tcsetpgrp(0, getpid());
	else if (signum == SIGTTOU)
		tcsetpgrp(0, getpid());
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
