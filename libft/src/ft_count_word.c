/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 18:53:03 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/06 19:21:40 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_count_word(char const *s, char c)
{
	unsigned int	nb_part;
	int				in_substr;

	nb_part = 0;
	in_substr = 0;
	while (*s)
	{
		if (in_substr && *s == c)
			in_substr = 0;
		if (!in_substr && *s != c)
		{
			in_substr = 1;
			nb_part++;
		}
		s++;
	}
	return (nb_part);
}
