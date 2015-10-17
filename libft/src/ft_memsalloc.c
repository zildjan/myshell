/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memsalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 16:29:38 by pbourrie          #+#    #+#             */
/*   Updated: 2014/11/15 16:01:11 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memsalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr("FATAL ERROR: memory allocation failed, ");
		ft_putendl("exit to prevent indeterminate behavior...");
		exit(1);
	}
	ft_memset(ptr, 0, size);
	return (ptr);
}
