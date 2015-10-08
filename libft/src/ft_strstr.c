/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 19:59:19 by pbourrie          #+#    #+#             */
/*   Updated: 2014/11/06 20:05:31 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	unsigned int i;

	if (!s2 || !*s2)
		return ((char *)s1);
	while (*s1)
	{
		i = 0;
		while (s1[i] == s2[i])
		{
			i++;
			if (!s2[i])
				return ((char *)s1);
		}
		s1++;
	}
	return (NULL);
}
