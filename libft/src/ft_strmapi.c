/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 16:20:16 by pbourrie          #+#    #+#             */
/*   Updated: 2014/11/14 19:09:06 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
			new[i] = f(i, s[i]);
			i++;
		}
		return (new);
	}
	else
		return (NULL);
}
