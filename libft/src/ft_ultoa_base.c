/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 15:12:19 by pbourrie          #+#    #+#             */
/*   Updated: 2015/02/16 19:24:28 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	add_pos(unsigned long long n, char *str, size_t base, char *nums)
{
	if (n >= base)
	{
		add_pos(n / base, str - 1, base, nums);
	}
	*str = nums[n % base];
}

char		*ft_ultoa_base(unsigned long long n, size_t base)
{
	char	*str;
	size_t	size;
	char	nums[33];

	ft_strcpy(nums, "0123456789abcdefghijklmopqrstuvw");
	if (base > 32)
		base = 32;
	if (base < 2)
		base = 2;
	size = ft_u_nbrlen_base(n, base);
	str = ft_strnew(size + 1);
	if (!str)
		return (NULL);
	add_pos(n, (str + size - 1), base, nums);
	*(str + size) = '\0';
	return (str);
}
