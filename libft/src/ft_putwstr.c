/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/25 20:59:59 by pbourrie          #+#    #+#             */
/*   Updated: 2015/02/25 22:10:08 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putwstr(const wchar_t *s)
{
	int		a;
	size_t	ret;

	a = 1;
	ret = 0;
	if (s)
	{
		while (*s)
		{
			if ((a = ft_putwchar(*s)) == -1)
				return (-1);
			s++;
			ret += a;
		}
	}
	return (ret);
}
