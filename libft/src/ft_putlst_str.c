/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlst_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 19:25:34 by pbourrie          #+#    #+#             */
/*   Updated: 2014/11/15 19:25:46 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlst_str(t_list **alst)
{
	if (*alst)
	{
		while ((*alst)->next)
		{
			ft_putstr((*alst)->content);
			ft_putstr(" - ");
			*alst = (*alst)->next;
		}
		ft_putstr((*alst)->content);
	}
}
