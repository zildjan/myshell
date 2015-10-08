/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/10 22:27:38 by pbourrie          #+#    #+#             */
/*   Updated: 2015/03/13 21:55:41 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define CT_NB_TAG 12

# define CT_CLEAR "\033[0m"

# define CT_YELLOW "\033[33m"
# define CT_RED "\033[31m"
# define CT_GREEN "\033[32m"
# define CT_CYAN "\033[36m"
# define CT_WHITE "\033[37m"
# define CT_BLUE "\033[34m"

# define CT_BOLD "\033[1m"
# define CT_UNDER_LINE "\033[4m"

# define CT_TAG_BEGIN '{'
# define CT_TAG_END '}'

typedef struct	s_color_tag
{
	char		tag[15];
	char		name[15];
}				t_color_tag;

void			load_color_tags(t_color_tag *color_tag);
int				put_color(const char *format, int pos, t_color_tag *color);

#endif
