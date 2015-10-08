/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/25 20:44:09 by pbourrie          #+#    #+#             */
/*   Updated: 2015/02/25 20:45:17 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_btoi(const char *str)
{
	int	res;
	int	n;

	n = -1;
	res = 0;
	while (ft_isspace(*str))
		str++;
	if ((*str == '+' || *str == '-') && !ft_isdigit(*(str + 1)))
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str) && ft_isdigit(*(str + 1)))
		str++;
	while (ft_isdigit(*str))
	{
		if ((n++ >= 9 && *str > 2 && res < -147483648 && *str != 0))
			return (0);
		if (*str-- != '0')
			res -= (*(str + 1) - '0') * ft_pow(2, n);
	}
	if (*str != '-' && res != 0 && res > -2147483648)
		res = -res;
	else if (*str != '-' && res == -2147483648)
		return (0);
	return (res);
}
