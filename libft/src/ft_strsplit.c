/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 15:56:45 by pbourrie          #+#    #+#             */
/*   Updated: 2014/12/10 17:01:19 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		get_part_len(char const *s, char c)
{
	size_t len;

	len = 0;
	while (*s && *s != c)
	{
		s++;
		len++;
	}
	return (len);
}

char				**ft_strsplit(char const *s, char c)
{
	char			**tab;
	unsigned int	i;
	unsigned int	nb_part;

	tab = NULL;
	if (s && c)
	{
		i = 0;
		nb_part = ft_count_word(s, c);
		tab = (char **)malloc(sizeof(char*) * (nb_part + 1));
		if (tab == NULL)
			return (NULL);
		while (i < nb_part)
		{
			while (*s == c)
				s++;
			tab[i] = ft_strsub(s, 0, get_part_len(s, c));
			if (tab[i] == NULL)
				return (NULL);
			s += get_part_len(s, c);
			i++;
		}
		tab[i] = 0;
	}
	return (tab);
}
