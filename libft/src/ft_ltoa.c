/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 15:12:19 by pbourrie          #+#    #+#             */
/*   Updated: 2015/02/14 19:04:02 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	add_neg(long long n, char *str)
{
	if (n <= -10)
	{
		add_neg(n / 10, str - 1);
	}
	*str = ('0' + ((n % 10) * -1));
}

static void	add_pos(long long n, char *str)
{
	if (n >= 10)
	{
		add_pos(n / 10, str - 1);
	}
	*str = ('0' + n % 10);
}

char		*ft_ltoa(long long n)
{
	char	*str;
	size_t	size;

	size = ft_nbrlen(n);
	str = ft_strnew(size + 1);
	if (!str)
		return (NULL);
	if (n >= 0)
		add_pos(n, (str + size - 1));
	else
		add_neg(n, (str + size - 1));
	if (n < 0)
		*str = '-';
	*(str + size) = '\0';
	return (str);
}
