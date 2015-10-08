/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/25 20:55:37 by pbourrie          #+#    #+#             */
/*   Updated: 2015/02/27 21:07:19 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

wchar_t		*ft_wstrdup(const wchar_t *s1)
{
	int		size;
	wchar_t	*s2;

	if (s1 == NULL)
		return (NULL);
	size = 0;
	while (s1[size])
		size++;
	s2 = (wchar_t*)ft_memalloc((sizeof(wchar_t) * (size + 1)));
	if (!s2)
		return (0);
	ft_memcpy(s2, s1, size * sizeof(wchar_t));
	return (s2);
}
