/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 16:03:45 by pbourrie          #+#    #+#             */
/*   Updated: 2014/11/14 19:08:35 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*new;
	size_t			size;
	unsigned int	i;

	if (s && f)
	{
		size = ft_strlen(s);
		new = ft_strnew(size + 1);
		if (!new)
			return (NULL);
		i = 0;
		while (s[i])
		{
			new[i] = f(s[i]);
			i++;
		}
		return (new);
	}
	return (NULL);
}
