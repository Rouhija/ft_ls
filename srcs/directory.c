/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 16:04:33 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/17 14:30:04 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** 		Read contents of a directory to a linked list
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
		(*ls)->width = ft_strlen(obj->name) > (*ls)->width ?
						ft_strlen(obj->name) : (*ls)->width;
	}
	closedir(dir);
}

/*
** 		Read contents of a directory to a linked list (including hidden files)
*/

void			read_dir_a(t_ls **ls, t_obj **head, char *dirname)
{
	struct dirent			*dp;
	t_obj					*obj;
	DIR						*dir;

	if (!(dir = opendir(dirname)))
		exit_program(1);
	while ((dp = readdir(dir)))
	{
		obj = new_obj(dirname, (*dp).d_name);
		addlst(head, obj);
		(*ls)->objs++;
		(*ls)->total += obj->st_blocks;
		(*ls)->width = ft_strlen(obj->name) > (*ls)->width ?
						ft_strlen(obj->name) : (*ls)->width;
	}
	closedir(dir);
}