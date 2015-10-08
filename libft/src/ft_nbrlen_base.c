/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:25:32 by pbourrie          #+#    #+#             */
/*   Updated: 2015/02/14 20:15:24 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_nbrlen_base(long long n, int base)
{
	unsigned int i;

	i = 1;
	if (n < 0)
		i++;
	while (n >= base || n <= (base * -1))
	{
		i++;
		n /= base;
	}
	return (i);
}
