/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 15:12:19 by pbourrie          #+#    #+#             */
/*   Updated: 2015/05/26 20:17:28 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

static int	add_f_int(char *str, size_t size, int precision)
{
	size_t	pos;

	pos = size;
	while (pos--)
	{
		str--;
		if (*str == '9' && precision <= 0)
			*str = '0';
		else if (ft_isdigit(*str) && precision <= 0)
		{
			*str += 1;
			return (0);
		}
		precision--;
	}
	str += size;
	while (size--)
	{
		*(str + 1) = *str;
		str--;
	}
	*(str + 1) = '1';
	return (1);
}

static int	add_float(double fpart, int precision, char *str)
{
	*str = '.';
	while (precision > 0)
	{
		str++;
		fpart *= 10;
		*str = ('0' + (long)fpart);
		fpart -= (long)fpart;
		precision--;
	}
	fpart *= 10;
	if ((long)fpart >= 5)
	{
		*str += 1;
		while (*str > '9')
		{
			*str = '0';
			if (*(str - 1) != '.')
				*(str - 1) += 1;
			else if (*(str - 1) == '.')
				return (1);
			str--;
		}
	}
	return (0);
}

char		*ft_dtoa(double n, int precision)
{
	char	*str;
	size_t	size;
	long	ipart;
	double	fpart;
	char	*temp;

	ipart = (long)n;
	fpart = n - ipart;
	size = ft_nbrlen(ipart);
	if (fpart < 0)
		fpart *= -1;
	if (n > -1 && n < 0)
		size++;
	if (precision > 0)
		precision++;
	if ((str = ft_strnew(size + precision + 1)) == NULL)
		return (NULL);
	temp = ft_ltoa(ipart);
	ft_strcpy(str, temp);
	free(temp);
	if (n > -1 && n < 0)
		ft_strcpy(str, "-0");
	if (add_float(fpart, precision - 1, str + size))
		add_f_int(str + size + precision, size + precision + 1, precision - 1);
	return (str);
}
