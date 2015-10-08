/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 20:33:19 by pbourrie          #+#    #+#             */
/*   Updated: 2014/11/14 19:48:46 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	trimlen(char const *s)
{
	unsigned int	i;
	size_t			space;
	size_t			len;

	i = 0;
	len = ft_strlen(s);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	space = i;
	if (s[i])
	{
		i = len - 1;
		while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		{
			space++;
			i--;
		}
	}
	return (len - space);
}

char			*ft_strtrim(char const *s)
{
	char			*str;
	size_t			len;
	unsigned int	i;

	if (!s)
		return (NULL);
	len = trimlen(s);
	str = ft_strnew(len + 1);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	i = 0;
	while (i < len)
	{
		str[i] = *s;
		s++;
		i++;
	}
	return (str);
}
