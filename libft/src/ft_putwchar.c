/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/25 20:32:14 by pbourrie          #+#    #+#             */
/*   Updated: 2015/02/27 21:44:33 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_mask(int n)
{
	char *s;

	if (n < 8)
		s = ft_strdup("0xxxxxxx");
	else if (n >= 8 && n < 12)
		s = ft_strdup("110xxxxx10xxxxxx");
	else if (n >= 12 && n < 17)
		s = ft_strdup("1110xxxx10xxxxxx10xxxxxx");
	else
		s = ft_strdup("11110xxx10xxxxxx10xxxxxx10xxxxxx");
	return (s);
}

static char	*fill_mask(char *x, char *s)
{
	while (*x)
	{
		*(ft_strrchr(s, 'x')) = *x;
		x++;
	}
	while (ft_strrchr(s, 'x'))
		*(ft_strrchr(s, 'x')) = '0';
	return (s);
}

static int	*mask_to_tab(char *bin, char *s)
{
	char	*x;
	int		a;
	int		i;
	int		*nb;

	i = 0;
	a = 0;
	x = bin;
	if (!(nb = (int *)ft_memalloc(sizeof(int) * 4)))
		return (NULL);
	while (s[i])
	{
		x = ft_strndup((s + i), 8);
		nb[a++] = ft_btoi(x);
		i += 8;
		free(x);
	}
	return (nb);
}

int			ft_putwchar(wchar_t c)
{
	size_t	n;
	char	*x;
	char	*s;
	int		*nb;

	if (!c)
	{
		write(1, "\0", 1);
		return (1);
	}
	if (c > 0x10FFFF)
		return (-1);
	x = ft_ultoa_base((unsigned int)c, 2);
	if (!(s = fill_mask(x, get_mask(ft_strlen(ft_strrev(x))))))
		return (-1);
	if (!(nb = mask_to_tab(x, s)))
		return (-1);
	free(x);
	free(s);
	n = 0;
	while (nb[n])
		write(1, &(nb[n++]), 1);
	free(nb);
	return (n);
}
