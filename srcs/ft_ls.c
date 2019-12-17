/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:29:34 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/17 13:09:01 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			recurse_dirs(t_ls **ls, char *dirname)
{
	char					*next;
	t_obj					*head;
	int						index;

	(*ls)->width = 0;
	(*ls)->total = 0;
	head = NULL;
	read_dir(ls, &head, dirname);
	ft_printf("%s:\ntotal %d\n", dirname, (*ls)->total / 2);
	// ft_printf("max width: %zu total %zu count %d\n", (*ls)->width, (*ls)->total, (*ls)->objs);
	(*ls)->flags & LLIST ? objiter(head, ls, print_obj_long) : objiter(head, ls, print_obj_short);
	ft_putchar('\n');
	index = 1;
	while ((next = lst_search(head, 0, index)))
	{
		ft_putendl(next);
		index++;
		recurse_dirs(ls, next);
		free(next);
	}
	// ft_printf("%s\n", (next));
	objiter(head, ls, object_del);
}

void			ft_ls(t_ls **ls)
{
	t_obj	*head;

	head = NULL;
	read_dir(ls, &head, (*ls)->dirname);
	objiter(head, ls, print_obj_long);
	objiter(head, ls, print_obj_short);
	recurse_dirs(ls, (*ls)->dirname);
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
