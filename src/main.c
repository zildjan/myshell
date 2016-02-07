/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/09 12:18:49 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/06 20:29:40 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		main(int argc, char **argv, char **environ)
{
	t_env	*e;

	e = init_env(argc, argv, environ);
	sig_handler(e, 0);
	catch_signal();
	while (1)
	{
		if (isatty(0))
		{
			gen_prompt(e, NULL);
			print_prompt(e);
		}
		get_cmd(e);
	}
	return (0);
}
