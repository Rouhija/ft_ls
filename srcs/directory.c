/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 16:04:33 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/17 12:56:45 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** 		Read contents of a directory to binary tree in reverse ascii order
*/

void			read_dir(t_ls **ls, t_obj **head, char *dirname)
{
	struct dirent			*dp;
	t_obj					*obj;
	DIR						*dir;

	if (!(dir = opendir(dirname)))
		exit_program(1);
	while ((dp = readdir(dir)))
	{
		if ((*dp).d_name[0] == '.')
			continue ;
		obj = new_obj(dirname, (*dp).d_name);
		addlst(head, obj);
		(*ls)->objs++;
		(*ls)->total += obj->st_blocks;
		(*ls)->width = ft_strlen(obj->name) > (*ls)->width ? ft_strlen(obj->name) : (*ls)->width;
	}
	closedir(dir);
}