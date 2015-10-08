/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 16:26:56 by pbourrie          #+#    #+#             */
/*   Updated: 2014/11/15 19:09:04 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	if (alst)
	{
		while ((*alst)->next)
		{
			tmp = *alst;
			*alst = (*alst)->next;
			del(tmp, tmp->content_size);
		}
		del(*alst, (*alst)->content_size);
		*alst = NULL;
	}
}
