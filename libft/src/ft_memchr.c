/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 16:27:12 by pbourrie          #+#    #+#             */
/*   Updated: 2014/11/08 16:57:24 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	if (!s || !n)
		return (NULL);
	str = (unsigned char*)s;
	while (n)
	{
		if (*str == (unsigned char)c)
			return ((void*)str);
		n--;
		str++;
	}
	return (NULL);
}
