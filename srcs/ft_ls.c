/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:29:34 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/17 19:22:51 by srouhe           ###   ########.fr       */
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
		(*ls)->dirs ? ft_printf("%s:\n", (*ls)->dirname) : PASS;
		head = NULL;
		(*ls)->flags & HIDDEN ? read_dir_a(ls, &head, (*ls)->dirname) : read_dir(ls, &head, (*ls)->dirname);
		merge_sort(&head, ls);
		if ((*ls)->flags & LLIST)
		{
			ft_printf("total %d\n", (*ls)->total);
			objiter(&head, ls, print_obj_long);
		}
		else
		{
			columns(ls);
			(*ls)->cols ? objiter(&head, ls, print_obj_cols) : objiter(&head, ls, print_obj_short);
			ft_putchar('\n');
		}
		objiter(&head, ls, object_del);
	}
	(*ls)->width = 0;
	(*ls)->total = 0;
	(*ls)->objs = 0;
	(*ls)->w_uid = 0;
	(*ls)->w_gid = 0;
	(*ls)->w_size = 0;
	(*ls)->w_links = 0;
}
