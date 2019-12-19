/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:28:51 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/19 11:43:58 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			recurse_dirs(t_ls **ls, char *dirname)
{
	char					*next;
	t_obj					*head;
	int						index;

	reset_dir(ls);
	head = NULL;
	(*ls)->flags & HIDDEN ? read_dir_a(ls, &head, dirname) : read_dir(ls, &head, dirname);
	merge_sort(&head, ls);
	ft_printf("%s:\n", dirname);
	(*ls)->flags & LLIST && (*ls)->objs ? ft_printf("total %d\n", (*ls)->total) : PASS;
	if ((*ls)->flags & LLIST)
		objiter(&head, ls, print_obj_long);
	else
	{
		columns(ls);
		(*ls)->cols ? objiter(&head, ls, print_obj_cols) : objiter(&head, ls, print_obj_short);
	}
	index = 1;
	while ((next = lst_search(head, 0, index)))
	{
		(*ls)->flags & LLIST ? ft_putchar('\n') : ft_putstr("\n\n");
		index++;
		recurse_dirs(ls, next);
		free(next);
	}
	objiter(&head, ls, object_del);
}
