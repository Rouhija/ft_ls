/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:29:34 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/18 20:43:56 by srouhe           ###   ########.fr       */
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
		(*ls)->ac > 1 ? ft_printf("%s:\n", (*ls)->dirname) : PASS;
		head = NULL;
		(*ls)->flags & HIDDEN ? read_dir_a(ls, &head, (*ls)->dirname) : read_dir(ls, &head, (*ls)->dirname);
		merge_sort(&head, ls);
		if ((*ls)->flags & LLIST)
		{
			ft_printf("total %d\n", (*ls)->total / 2);
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
	reset_dir(ls);
}
