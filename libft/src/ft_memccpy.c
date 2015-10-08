/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 21:36:30 by pbourrie          #+#    #+#             */
/*   Updated: 2014/11/07 22:22:11 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*src2;
	unsigned char	*dst2;
	unsigned char	c2;

	dst2 = (unsigned char*)dst;
	src2 = (unsigned char*)src;
	c2 = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		*(dst2 + i) = *(src2 + i);
		if (*(dst2 + i) == c2)
			return (dst2 + i + 1);
		i++;
	}
	return (NULL);
}
