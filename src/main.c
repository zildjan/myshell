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

	signal(SIGINT, sighandler);

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
//	ft_printf("Caught signal %d, coming out...\n", signum);
	if (signum != 239)
		print_prompt();
//	exit(1);
}
