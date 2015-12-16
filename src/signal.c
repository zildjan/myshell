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
	signal(SIGSEGV, sig_mediator);
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
	if (signum == SIGINT)
	{
//		print_prompt(se);
	}/*
	else if (signum == SIGSEGV || signum == SIGABRT)
	{
		ft_printf("!!!!!! SEGVAULT\n");

		ft_printf("\n\n\nline = '%s'\n->", se->line);
		int i;
		i = 0;
		while (se->line[i])
		{
			if (ft_isalnum(se->line[i]))
				ft_putchar(se->line[i]);
			i++;
		}
		ft_printf("<-\n");
		i = 0;
		while (se->line[i])
		{
			ft_putnbr(se->line[i]);
			ft_putchar(' ');
			i++;
		}
		ft_printf("<-\n");
//		while (1)
		exit(1);
	}  // */
	else if (signum == SIGTSTP)
	{		
//		ft_printf("STOP %ld\n", se->jobs->pid);
//		if (se->jobs && se->jobs->pid)
//			kill(se->jobs->pid, SIGTSTP);
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
