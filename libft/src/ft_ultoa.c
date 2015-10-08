/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 15:12:19 by pbourrie          #+#    #+#             */
/*   Updated: 2015/02/14 19:27:23 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	add_pos(unsigned long long n, char *str)
{
	if (n >= 10)
	{
		add_pos(n / 10, str - 1);
	}
	*str = ('0' + n % 10);
}

char		*ft_ultoa(unsigned long long n)
{
	char	*str;
	size_t	size;

	size = ft_u_nbrlen(n);
	str = ft_strnew(size + 1);
	if (!str)
		return (NULL);
	add_pos(n, (str + size - 1));
	*(str + size) = '\0';
	return (str);
}
