/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcharlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/25 20:53:40 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/13 20:37:56 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wcharlen(wchar_t c)
{
	int		n;
	char	*bin;

	bin = ft_ultoa_base((unsigned long)c, 2);
	n = ft_strlen(bin);
	free(bin);
	if (n <= 7)
		return (1);
	else if (n >= 8 && n < 12)
		return (2);
	else if (n >= 12 && n < 17)
		return (3);
	else if (n >= 17)
		return (4);
	else
		return (0);
}
