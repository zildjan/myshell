/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 15:12:19 by pbourrie          #+#    #+#             */
/*   Updated: 2015/02/14 19:02:40 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	add_neg(int n, char *str)
{
	if (n <= -10)
	{
		add_neg(n / 10, str - 1);
	}
	*str = ('0' + ((n % 10) * -1));
}

static void	add_pos(int n, char *str)
{
	if (n >= 10)
	{
		add_pos(n / 10, str - 1);
	}
	*str = ('0' + n % 10);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		size;

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
