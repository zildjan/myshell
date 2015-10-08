/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 18:23:48 by pbourrie          #+#    #+#             */
/*   Updated: 2014/11/08 18:33:04 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	unsigned int i;
	unsigned int j;

	j = 0;
	if (!s2 || !*s2)
		return ((char *)s1);
	while (*s1 && j < n)
	{
		i = 0;
		while (s1[i] == s2[i] && ((i + j) < n))
		{
			i++;
			if (!s2[i])
				return ((char *)s1);
		}
		s1++;
		j++;
	}
	return (NULL);
}
