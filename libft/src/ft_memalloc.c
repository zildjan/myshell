/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 16:29:38 by pbourrie          #+#    #+#             */
/*   Updated: 2016/05/22 00:36:08 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*ptr;

	ptr = NULL;
	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("FATAL ERROR: memory allocation failed, ", 2);
		ft_putendl_fd("exit to prevent indeterminate behavior...", 2);
		exit(1);
	}
	ft_memset(ptr, 0, size);
	return (ptr);
}
