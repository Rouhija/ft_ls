/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 12:56:20 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/17 14:58:55 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	objiter(t_obj **lst, t_ls **ls, void (*applyf)(t_obj **, t_ls **))
{
    t_obj   *tmp;

    tmp = *lst;
	if (tmp)
	{
		while (tmp)
		{
			applyf(&tmp, ls);
			tmp = tmp->next;
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
			if (lst->rights[0] == 'd' && ft_strcmp(lst->name, ".")
									&& ft_strcmp(lst->name, ".."))
            {
                i++;
                if (i == index)
                    return (ft_strdup(lst->path));           
            }
			lst = lst->next;
		}
	}
    return (NULL);
}
