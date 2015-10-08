/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrndup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/25 20:55:37 by pbourrie          #+#    #+#             */
/*   Updated: 2015/02/27 22:26:24 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	find_nb_wchar(const wchar_t *s, size_t n)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (s)
		while (*s)
		{
			i += ft_wcharlen(*s);
			if (i <= n)
				len++;
			else
				break ;
			s++;
		}
	return (len);
}

wchar_t			*ft_wstrndup(const wchar_t *s1, size_t n)
{
	int		len;
	wchar_t	*s2;

	if (s1 == NULL)
		return (NULL);
	len = find_nb_wchar(s1, n);
	s2 = (wchar_t *)ft_memalloc(sizeof(wchar_t) * (len + 1));
	if (!s2)
		return (0);
	ft_memcpy(s2, s1, len * sizeof(wchar_t));
	return (s2);
}
