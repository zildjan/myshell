/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourrie <pbourrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 17:28:52 by pbourrie          #+#    #+#             */
/*   Updated: 2016/01/27 17:34:56 by pbourrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static long    sort_cmp(char **stab, char *piv, long i)
{
	return (ft_strcmp(stab[i], piv));
}

static void    switch_piv(char **stab, long l, long r)
{
    char	*temp;

    temp = stab[l];
    stab[l] = stab[r];
    stab[r] = temp;
}

void    myqsort(char **stab, int beg, int end)
{
    char	   *piv;
    long        l;
    long        r;

    if (end > beg)
    {
        piv = stab[beg];
        l = beg + 1;
        r = end;
        while (l < r)
            if (sort_cmp(stab, piv, l) <= 0)
                l++;
            else if (sort_cmp(stab, piv, r) >= 0)
                r--;
            else
                switch_piv(stab, l, r);
        if (sort_cmp(stab, piv, l) < 0)
            switch_piv(stab, l--, beg);
        else
            switch_piv(stab, --l, beg);
        myqsort(stab, beg, l);
        myqsort(stab, r, end);
    }
}
