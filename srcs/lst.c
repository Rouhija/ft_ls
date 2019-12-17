/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:56:20 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/17 13:09:11 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	objiter(t_obj *lst, t_ls **ls, void (*applyf)(t_obj *, t_ls **))
{
	if (lst)
	{
		while (lst)
		{
			applyf(lst, ls);
			lst = lst->next;
		}
	}
}

void	addlst(t_obj **alst, t_obj *new)
{
	if (alst && *alst)
	{
		new->next = *alst;
		*alst = new;
	}
	else
		*alst = new;
}

char    *lst_search(t_obj *lst, int i, int index)
{
	if (lst)
	{
		while (lst)
		{
			if (lst->rights[0] == 'd' && lst->name[0] != '.')
            {
                i++;
                // ft_printf("current %d, index %d\n", i, index);
                if (i == index)
                {
                    // ft_putendl(lst->path);
                    return (ft_strdup(lst->path));
                }               
            }
			lst = lst->next;
		}
	}
    return (NULL);
}
