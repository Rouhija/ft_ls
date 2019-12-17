/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:59:17 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/17 16:02:55 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** 		Get right padding based on current shell size
*/

static int		get_padding(t_ls **ls, int ws_col)
{
	struct winsize	w;
	int				width;

	width = (*ls)->width;
	ioctl(1, TIOCGSIZE, &w);
	if (width < 16 && (*ls)->objs * 16 < ws_col)
		return (16);
	else if ((*ls)->width < 24)
		return (24);
	else
		return(width + 6);	
}

/*
**		Print ls -l format
*/

void			print_obj_long(t_obj **head, t_ls **ls)
{
	t_obj			*obj;

	obj = *head;
	ft_printf("%-10s %d %-7s %.4s %6zu %.12s %s\n", 
		obj->rights,
		obj->st_nlink, // check length!!
		obj->st_uid,
		&obj->dt[16],
		obj->st_size,
		obj->dt,
		obj->name
	);
}

/*
**		Print with columnar format
**		Reset cursor \033[l;cH 
**		Up n lines \033[nA
**		forward n characters \033[nC
**		Store cursor \033[s Move back to it \033[u
*/

void			print_obj_short(t_obj **head, t_ls **ls)
{
	struct winsize	w;
	static int		i;
	int				cols;
	int				rows;
	int				padding;
	t_obj			*obj;

	obj = *head;
	ioctl(1, TIOCGSIZE, &w);
	padding = get_padding(ls, w.ws_col);
	cols = w.ws_col / (*ls)->width + 2;
	rows = cols / (*ls)->objs;
	i++;
	if (obj->rights[0] == 'd')
		ft_putstr("\033[01;32m");
	// ft_putstr("\033[10A");
	// ft_printf("%d", padding);
	ft_printf("%-*s", (*ls)->width + 2, obj->name); // HERE IS THE PROBLEM!! CHECK COLUMNAR FORMAT
	if (obj->rights[0] == 'd')
		ft_putstr("\033[0m");
	if (cols == i)
	{
		ft_putchar('\n');
		i = 0;
	}
}