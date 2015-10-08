/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 19:10:53 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/23 21:51:47 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstsplit(char const *s, char c, int keepc)
{
	t_list	*begin;
	char	*str;
	int		x;

	if (!s)
		return (NULL);
	str = (char *)s;
	begin = NULL;
	while (*str)
	{
		x = 0;
		if (!keepc)
			while (*str == c && *str)
				str++;
		if (!*str)
			break ;
		while (str[x] != c && str[x])
			x++;
		if (keepc == 1 && str[x])
			x++;
		ft_lstaddend(&begin, ft_lstnew(str, (x + 1)));
		str = &str[x];
	}
	return (begin);
}
