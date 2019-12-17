/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:59:17 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/17 19:27:36 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**		Print ls -l format
*/

void			print_obj_long(t_obj **head, t_ls **ls)
{
	t_obj			*obj;

	// ft_printf("%lu <> %lu\n", (unsigned long)time(NULL) - SIXMON, obj->st_time);
	obj = *head;
	if ((unsigned long)time(NULL) - SIXMON < obj->st_time)
		ft_printf("%s  %*d %-*s %-*s %*zu %.12s ", 
			obj->rights,
			(*ls)->w_links, obj->st_nlink,
			(*ls)->w_uid + 1, obj->st_uid,
			(*ls)->w_gid + 1, obj->st_gid,
			(*ls)->w_size, obj->st_size,
			obj->dt
		);
	else
		ft_printf("%s  %*d %-*s %.4s %*zu %.12s ", 
			obj->rights,
			(*ls)->w_links, obj->st_nlink,
			(*ls)->w_uid + 1, obj->st_uid,
			&obj->dt[16],
			(*ls)->w_size, obj->st_size,
			obj->dt
		);
	if (obj->rights[0] == 'd')
		ft_putstr("\033[0;34m");
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
	static int		i;
	t_obj			*obj;

	obj = *head;
	if (obj->rights[0] == 'd')
		ft_putstr("\033[0;34m");
	ft_printf("%-*s", (*ls)->width + 7, obj->name);
	i++;
	if (i == (*ls)->cols)
	{
		ft_putchar('\n');
		i = 0;
	}
	if (obj->rights[0] == 'd')
		ft_putstr("\033[0m");
}
