/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/30 22:27:45 by pbourrie          #+#    #+#             */
/*   Updated: 2016/02/01 00:58:34 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memrealloc(void *ptr, size_t size, size_t new_size)
{
	void	*new;

	new = ft_memalloc(new_size);
	if (!new)
		return (NULL);
	if (size <= new_size)
		ft_memcpy(new, ptr, size);
	else
		ft_memcpy(new, ptr, new_size);
	free(ptr);
	return (new);
}
