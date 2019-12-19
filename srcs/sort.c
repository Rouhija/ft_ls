/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:44:09 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/19 12:19:53 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void front_back_split(t_obj *src, t_obj **frontref, t_obj **backref) 
{ 
    t_obj *fast; 
    t_obj *slow; 

    slow = src; 
    fast = src->next; 
    while (fast != NULL)
    { 
        fast = fast->next; 
        if (fast != NULL)
        { 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
    *frontref = src; 
    *backref = slow->next; 
    slow->next = NULL; 
}

static t_obj   *sorted_merge(t_obj *a, t_obj *b) 
{ 
    t_obj   *r;
    
    r = NULL;
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    if (ft_strcmp(a->name, b->name) < 0)
    {
        r = a; 
        r->next = sorted_merge(a->next, b); 
    }
    else
    { 
        r = b; 
        r->next = sorted_merge(a, b->next); 
    }
    return (r); 
}

static t_obj   *sorted_merge_rev(t_obj *a, t_obj *b) 
{ 
    t_obj   *r;
    
    r = NULL;
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    if (ft_strcmp(b->name, a->name) < 0)
    {
        r = a; 
        r->next = sorted_merge_rev(a->next, b); 
    }
    else
    { 
        r = b; 
        r->next = sorted_merge_rev(a, b->next); 
    }
    return (r); 
}

static t_obj   *sorted_merge_time(t_obj *a, t_obj *b) 
{ 
    t_obj   *r;
    
    r = NULL;
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    if ((a->st_time > b->st_time) ||
        ((a->st_time == b->st_time) && (ft_strcmp(a->name, b->name) > 0)))
    {
        r = a; 
        r->next = sorted_merge_time(a->next, b); 
    }
    else
    { 
        r = b; 
        r->next = sorted_merge_time(a, b->next); 
    }
    return (r); 
} 

void            merge_sort(t_obj **headref, t_ls **ls)
{ 
    t_obj   *head;
    t_obj   *a; 
    t_obj   *b; 
  
    head = *headref;
    if (!head || !head->next)
        return ;
    front_back_split(head, &a, &b); 
    merge_sort(&a, ls); 
    merge_sort(&b, ls);
    if ((*ls)->flags & TSORT && (*ls)->flags & RSORT)
        *headref = sorted_merge_time_rev(a, b);
    else if ((*ls)->flags & TSORT)
        *headref = sorted_merge_time(a, b);
    else if ((*ls)->flags & RSORT)
        *headref = sorted_merge_rev(a, b);
    else
        *headref = sorted_merge(a, b); 
}
