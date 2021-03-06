/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 12:18:49 by pbourrie          #+#    #+#             */
/*   Updated: 2016/09/08 23:03:43 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		main(int argc, char **argv, char **environ)
{
	t_env	*e;

	e = init_env(environ);
	sig_handler(e, 0);
	catch_signal();
	if (argc > 1)
		return (execute_script(e, argv[1], 1));
	load_rc(e);
	while (1)
	{
		if (isatty(e->fd_in))
		{
			gen_prompt(e, NULL);
			print_prompt(e);
		}
		get_cmd(e);
	}
	return (0);
}
