/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:59:17 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/19 12:37:44 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**		Print ls -l format
*/

void			print_obj_long(t_obj **head, t_ls **ls)
{
	t_obj			*obj;

	obj = *head;
	if (time(NULL) - SIXMON < obj->st_time)
		ft_printf("%s  %*d %-*s %-*s %*zu %.12s ",
			obj->rights, (*ls)->w_links, obj->st_nlink,
			(*ls)->w_uid + 1, obj->st_uid,
			(*ls)->w_gid + 1, obj->st_gid,
			(*ls)->w_size, obj->st_size,
			obj->dt);
	else
		ft_printf("%s  %*d %-*s %.4s %*zu %.12s ",
			obj->rights, (*ls)->w_links, obj->st_nlink,
			(*ls)->w_uid + 1, obj->st_uid,
			&obj->dt[16], (*ls)->w_size + 1, obj->st_size,
			obj->dt);
	if (obj->rights[0] == 'd')
		ft_putstr("\033[0;34m");
	if (obj->rights[0] == 'l')
		ft_printf("%s\n", obj->link);
	else
		ft_printf("%s\n", obj->name);
	if (obj->rights[0] == 'd')
		ft_putstr("\033[0m");
}

void			print_obj_short(t_obj **head, t_ls **ls)
{
	t_obj			*obj;

	obj = *head;
	if (obj->rights[0] == 'd')
		ft_putstr("\033[0;34m");
	ft_printf("%-*s", (*ls)->width + 7, obj->name);
	if (obj->rights[0] == 'd')
		ft_putstr("\033[0m");
}

void			print_obj_cols(t_obj **head, t_ls **ls)
{
	t_obj			*obj;

	obj = *head;
	if (obj->rights[0] == 'd')
		ft_putstr("\033[0;34m");
	ft_printf("%-*s", (*ls)->width + 7, obj->name);
	(*ls)->index++;
	if ((*ls)->index == (*ls)->cols)
	{
		ft_putchar('\n');
		(*ls)->index = 0;
	}
	if (obj->rights[0] == 'd')
		ft_putstr("\033[0m");
}
