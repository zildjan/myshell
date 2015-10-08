/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u_nbrlen_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:25:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/02/16 19:25:04 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_u_nbrlen_base(unsigned long long n, size_t base)
{
	unsigned int i;

	i = 1;
	if (base < 2)
		base = 2;
	while (n >= base)
	{
		i++;
		n /= base;
	}
	return (i);
}
