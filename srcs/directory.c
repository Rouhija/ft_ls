/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 16:04:33 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/17 19:15:38 by srouhe           ###   ########.fr       */
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
		(*ls)->w_links = ft_count_digits(obj->st_nlink, 10) > (*ls)->w_links ?
						ft_count_digits(obj->st_nlink, 10) : (*ls)->w_links;
		(*ls)->w_uid = ft_strlen(obj->st_uid) > (*ls)->w_uid ?
						ft_strlen(obj->st_uid) : (*ls)->w_uid;
		(*ls)->w_gid = ft_strlen(obj->st_gid) > (*ls)->w_gid ?
						ft_strlen(obj->st_gid) : (*ls)->w_gid;
		(*ls)->w_size = ft_count_digits(obj->st_size, 10) > (*ls)->w_size ?
						ft_count_digits(obj->st_size, 10) : (*ls)->w_size;
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
		(*ls)->w_links = ft_count_digits(obj->st_nlink, 10) > (*ls)->w_links ?
						ft_count_digits(obj->st_nlink, 10) : (*ls)->w_links;
		(*ls)->w_uid = ft_strlen(obj->st_uid) > (*ls)->w_uid ?
						ft_strlen(obj->st_uid) : (*ls)->w_uid;
		(*ls)->w_gid = ft_strlen(obj->st_gid) > (*ls)->w_gid ?
						ft_strlen(obj->st_gid) : (*ls)->w_gid;
		(*ls)->w_size = ft_count_digits(obj->st_size, 10) > (*ls)->w_size ?
						ft_count_digits(obj->st_size, 10) : (*ls)->w_size;
	}
	closedir(dir);
}
