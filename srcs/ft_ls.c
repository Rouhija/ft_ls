/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:29:34 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/17 14:33:26 by srouhe           ###   ########.fr       */
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
		(*ls)->flags & RSORT ? PASS : merge_sort(&head);
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

// void			ft_ls(t_ls **ls)
// {
// 	if ((*ls)->flags & RECURSE)
// 		recurse_dirs(ls, (*ls)->dirname);
// 	else
// 	{
// 		if ((*ls)->flags & RSORT)
// 			read_dir(ls, &(*ls)->btree, (*ls)->dirname, btree_insert_rev);
// 		else if ((*ls)->flags & TSORT)
// 			read_dir(ls, &(*ls)->btree, (*ls)->dirname, btree_insert_time);
// 		else
// 			read_dir(ls, &(*ls)->btree, (*ls)->dirname, btree_insert);
// 		if ((*ls)->flags & LLIST)
// 		{
// 			ft_printf("total %d\n", (*ls)->total / 2);
// 			btree_apply_infix((*ls)->btree, ls, print_obj_long);
// 		}
// 		else
// 		{
// 			btree_apply_infix((*ls)->btree, ls, print_obj_short);
// 			ft_putchar('\n');
// 		}
// 		// object_del((*ls)->btree->item); // DOES NOT WORK WITH MULTIPLE DIR ARGUMENTS
// 		btree_del((*ls)->btree);
// 		(*ls)->btree = NULL;
// 	}
// 	(*ls)->width = 0;
// 	(*ls)->total = 0;
// 	(*ls)->objs = 0;
// }
