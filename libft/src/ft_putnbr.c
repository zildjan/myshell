/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 14:14:07 by pbourrie          #+#    #+#             */
/*   Updated: 2015/02/17 19:54:11 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnbr(long n)
{
	char	*str;
	size_t	len;

	str = ft_ltoa(n);
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}
