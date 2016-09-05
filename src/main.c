/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 12:18:49 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/05 01:58:36 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		main(int argc, char **argv, char **environ)
{
	t_env	*e;
//	struct termios *test;
//	test = ft_memalloc(sizeof(struct termios));

	e = init_env(environ);
	sig_handler(e, 0);
	catch_signal();
	if (argc > 1)
		return (execute_script(e, argv[1], 1));
	load_rc(e);
	while (1)
	{
//		ft_printf("pid=%d\n", tcgetpgrp(0));

//		while (ft_memcmp(test, e->term, sizeof(struct termios)) && try < 100)
//			{

//		tcgetattr(0, test);
//		ft_printf("diff=%d\n", ft_memcmp(test, e->term, sizeof(struct termios)));

// */
		if (isatty(e->fd_in))
		{
			gen_prompt(e, NULL);
			print_prompt(e);
		}
		get_cmd(e);

	}
	return (0);
}
