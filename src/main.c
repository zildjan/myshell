/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 12:18:49 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/13 19:44:31 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

#include <errno.h>

int		main(int argc, char **argv, char **environ)
{
	t_env	*e;

//	ft_printf("tty='%ld' n='%s'\n", ttyslot(), ttyname(2));
//	ft_printf("SDTIN %ld\n", STDIN_FILENO);
//	ft_printf("SDTOUT %ld\n", STDOUT_FILENO);
//	ft_printf("SDTERR %ld\n", STDERR_FILENO);

	e = init_env(argc, argv, environ);
	sig_handler(e, 0);
	catch_signal();

/*
	char *term;
	term = get_env_val(e, "TERM");

	if (tgetent(NULL, term) != 1)
		ft_printf("tgetent failed\n");
	if (isatty(0))
	{
		e->term = ft_memalloc(sizeof(struct termios));

		if (tcgetattr(0, e->term) == -1)
			ft_printf("tcgetattr failed\n");

	}
*/
	while (1)
	{
		print_prompt(e);
		get_cmd(e);
	}
	return (0);
}
