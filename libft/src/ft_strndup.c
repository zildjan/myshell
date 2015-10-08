/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 19:30:18 by pbourrie          #+#    #+#             */
/*   Updated: 2014/11/15 18:39:35 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*s2;

	if (!s1)
		return (NULL);
	s2 = ft_strnew(n + 1);
	if (!s2)
		return (NULL);
	ft_strncpy(s2, s1, n);
	return (s2);
}
