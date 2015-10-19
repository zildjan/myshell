/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 16:03:45 by pbourrie          #+#    #+#             */
/*   Updated: 2014/11/14 19:08:35 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcheck(char const *s, int (*f)(int))
{
	unsigned int	i;

	if (s && f)
	{
		i = 0;
		while (s[i])
		{
			if (!f(s[i]))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
