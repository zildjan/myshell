/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/11 19:55:50 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/13 21:57:24 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	load_color_tags(t_color_tag *color_tag)
{
	ft_strcpy(color_tag[0].tag, CT_CLEAR);
	ft_strcpy(color_tag[0].name, "rt");
	ft_strcpy(color_tag[1].tag, CT_YELLOW);
	ft_strcpy(color_tag[1].name, "yellow");
	ft_strcpy(color_tag[2].tag, CT_RED);
	ft_strcpy(color_tag[2].name, "red");
	ft_strcpy(color_tag[3].tag, CT_GREEN);
	ft_strcpy(color_tag[3].name, "green");
	ft_strcpy(color_tag[4].tag, CT_CYAN);
	ft_strcpy(color_tag[4].name, "cyan");
	ft_strcpy(color_tag[5].tag, CT_WHITE);
	ft_strcpy(color_tag[5].name, "white");
	ft_strcpy(color_tag[6].tag, CT_BLUE);
	ft_strcpy(color_tag[6].name, "blue");
	ft_strcpy(color_tag[7].tag, CT_BOLD);
	ft_strcpy(color_tag[7].name, "bold");
	ft_strcpy(color_tag[8].tag, CT_UNDER_LINE);
	ft_strcpy(color_tag[8].name, "ul");
	ft_strcpy(color_tag[9].tag, CT_CLEAR);
	ft_strcpy(color_tag[9].name, "eoc");
	ft_strcpy(color_tag[10].tag, CT_CLEAR);
	ft_strcpy(color_tag[10].name, "clear");
	ft_strcpy(color_tag[11].tag, CT_CLEAR);
	ft_strcpy(color_tag[11].name, "reset");
}

int		put_color(const char *format, int pos, t_color_tag *color)
{
	int		i;
	int		id_color;

	i = 0;
	id_color = -1;
	while (++id_color < CT_NB_TAG)
	{
		while (format[pos + i + 1] == color[id_color].name[i])
		{
			i++;
			if (format[pos + i + 1] == CT_TAG_END)
			{
				ft_putstr(color[id_color].tag);
				return (i + 2);
			}
		}
		i = 0;
	}
	return (0);
}
