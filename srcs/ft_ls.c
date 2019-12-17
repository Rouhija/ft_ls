/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:29:34 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/17 14:56:49 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_ls(t_ls **ls)
{
	t_obj	*head;

	if ((*ls)->flags & RECURSE)
		recurse_dirs(ls, (*ls)->dirname);
	else
	{
		head = NULL;
		(*ls)->flags & HIDDEN ? read_dir_a(ls, &head, (*ls)->dirname) : read_dir(ls, &head, (*ls)->dirname);
		(*ls)->flags & RSORT ? PASS : merge_sort(&head, ls);
		if ((*ls)->flags & LLIST)
		{
			ft_printf("total %d\n", (*ls)->total / 2);
			objiter(&head, ls, print_obj_long);
		}
		else
		{
			objiter(&head, ls, print_obj_short);
			ft_putchar('\n');
		}
		objiter(&head, ls, object_del);
	}
	(*ls)->width = 0;
	(*ls)->total = 0;
	(*ls)->objs = 0;
}