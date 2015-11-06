/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strautosub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/11 17:51:52 by pbourrie          #+#    #+#             */
/*   Updated: 2015/11/06 19:22:33 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strautosub(char const *s, char start, char end)
{
	int		i;
	int		begin;
	int		len;

	if (!s)
		return (NULL);
	i = 0;
	begin = 0;
	while (s[i] && s[i++] != start && start > 0)
		begin++;
	if (begin)
		begin++;
	len = i;
	while (s[i] && (s[i++] != end || end < 0))
		len++;
	return (ft_strsub(s, begin, len));
}
