/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 12:18:49 by pbourrie          #+#    #+#             */
/*   Updated: 2015/10/09 21:08:54 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include <errno.h>

void sighandler(int);

int		main(void)
{
	t_env	*e;

//	signal(SIGINT, sighandler);
//	signal(SIGSEGV, sighandler);
//	signal(SIGBUS, sighandler);
//	signal(SIGTTIN, sighandler);
/*
	signal(1, sighandler);
	signal(2, sighandler);
	signal(3, sighandler);
	signal(4, sighandler);
	signal(5, sighandler);
	signal(6, sighandler);
	signal(7, sighandler);
	signal(8, sighandler);
	signal(9, sighandler);
	signal(10, sighandler);
	signal(11, sighandler);
	signal(12, sighandler);
	signal(13, sighandler);
	signal(14, sighandler);
	signal(15, sighandler);
	signal(16, sighandler);
	signal(17, sighandler);
	signal(18, sighandler);
	signal(19, sighandler);
	signal(20, sighandler);
	signal(21, sighandler);
	signal(22, sighandler);
	signal(23, sighandler);
	signal(24, sighandler);
	signal(25, sighandler);
	signal(26, sighandler);
	signal(27, sighandler);
	signal(28, sighandler);
	signal(29, sighandler);
	signal(30, sighandler);
	signal(31, sighandler);
// */

	e = init_env();

	while (1)
	{
		print_prompt();
		get_cmd(e);
	}

	return (0);
}


void sighandler(int signum)
{
	ft_printf("Caught signal %d, coming out...\n", signum);
	if (signum == SIGSEGV)
		ft_printf("Segmentation Fault ;)\n");
	else if (signum == SIGBUS)
		ft_printf("Bus error ;)\n");
		ft_printf("\n");
		print_prompt();
	exit(0);
}
