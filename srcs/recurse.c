/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:28:51 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/17 14:55:25 by srouhe           ###   ########.fr       */
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
	(*ls)->flags & HIDDEN ? read_dir_a(ls, &head, dirname) : read_dir(ls, &head, dirname);
	(*ls)->flags & RSORT ? PASS : merge_sort(&head, ls);
	ft_printf("%s:\ntotal %d\n", dirname, (*ls)->total / 2);
	(*ls)->flags & LLIST ? objiter(&head, ls, print_obj_long) : objiter(&head, ls, print_obj_short);
	ft_putchar('\n');
	index = 1;
	while ((next = lst_search(head, 0, index)))
	{
		index++;
		recurse_dirs(ls, next);
		free(next);
	}
	objiter(&head, ls, object_del);
}