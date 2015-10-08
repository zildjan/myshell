/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/25 20:58:37 by pbourrie          #+#    #+#             */
/*   Updated: 2015/02/27 20:48:12 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wstrlen(const wchar_t *s)
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	if (s)
		while (s[i] != 0)
		{
			size += ft_wcharlen(s[i]);
			i++;
		}
	return (size);
}
