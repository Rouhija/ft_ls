/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:29:34 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/19 12:26:04 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		list_dir(t_ls **ls)
{
	t_obj	*head;

	(*ls)->ac > 0 ? ft_printf("%s:\n", (*ls)->dirname) : PASS;
	head = NULL;
	(*ls)->flags & HIDDEN ? read_dir_a(ls, &head, (*ls)->dirname)
	: read_dir(ls, &head, (*ls)->dirname);
	merge_sort(&head, ls);
	if ((*ls)->flags & LLIST)
	{
		(*ls)->objs ? ft_printf("total %d\n", (*ls)->total) : PASS;
		objiter(&head, ls, print_obj_long);
	}
	else
	{
		columns(ls);
		(*ls)->cols ? objiter(&head, ls, print_obj_cols)
		: objiter(&head, ls, print_obj_short);
		ft_putchar('\n');
	}
	objiter(&head, ls, object_del);
}

void			ft_ls(t_ls **ls)
{
	if ((*ls)->flags & RECURSE)
		recurse_dirs(ls, (*ls)->dirname);
	else
		list_dir(ls);
	reset_dir(ls);
}
