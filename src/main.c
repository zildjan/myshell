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

int		main(int ac, char **av)
{
	pid_t	father;
	int		ret;

	father = fork();
	if (father > 0)
	{
		ft_printf("PERE =%ld\n", father);
		wait(&ret);
		ft_printf("PERE fin ret=%ld\n", ret);
	}
	else if (father == 0)
	{
		ft_printf("FILS\n");
		execve("a.out", av, NULL);
		ft_printf("FILS fin\n");
	}

	if (ac > 55)
		return (-1);
	return (0);
}
