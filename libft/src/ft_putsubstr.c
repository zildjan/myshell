/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsubstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 18:34:01 by pbourrie          #+#    #+#             */
/*   Updated: 2014/12/17 18:35:42 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putsubstr(char *str, int beg, int size)
{
	int i;

	i = -1;
	while (++i < (size + beg))
	{
		if (i >= beg)
			ft_putchar(str[i]);
	}
}
