/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 10:26:40 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/19 10:28:59 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_obj   *sorted_merge_time_rev(t_obj *a, t_obj *b) 
{ 
    t_obj   *r;
    
    r = NULL;
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    if (b->st_time > a->st_time)
    {
        r = a; 
        r->next = sorted_merge_time_rev(a->next, b); 
    }
    else
    { 
        r = b; 
        r->next = sorted_merge_time_rev(a, b->next); 
    }
    return (r); 
}
