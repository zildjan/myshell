/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 18:01:39 by pbourrie          #+#    #+#             */
/*   Updated: 2014/11/10 18:09:46 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char			*cur1;
	char			*cur2;
	unsigned int	i;

	cur1 = s1;
	cur2 = (char *)s2;
	i = 0;
	while (*cur1 != '\0')
		cur1++;
	while (*cur2 != '\0' && i < n)
	{
		*cur1 = *cur2;
		cur1++;
		cur2++;
		i++;
	}
	*cur1 = '\0';
	return (s1);
}
