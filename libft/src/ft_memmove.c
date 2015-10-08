/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 16:09:01 by pbourrie          #+#    #+#             */
/*   Updated: 2014/11/08 16:24:32 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *tmp;

	tmp = ft_memalloc(len);
	ft_memcpy(tmp, src, len);
	ft_memcpy(dst, tmp, len);
	ft_memdel((void*)&tmp);
	return (dst);
}
