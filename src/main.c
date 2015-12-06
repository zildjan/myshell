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

int		main(void)
{
	t_env	*e;

	ft_printf("tty='%ld' n='%s'\n", ttyslot(), ttyname(2));

	e = init_env();
	sig_handler(e, 0);
	catch_signal();
	while (1)
	{
		print_prompt(e);
		get_cmd(e);
	}
	return (0);
}
