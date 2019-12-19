/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 16:04:33 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/19 13:35:02 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		calc_paddings(t_ls **ls, t_obj *obj)
{
	(*ls)->total += obj->st_blocks;
	(*ls)->width = (int)ft_strlen(obj->name) > (*ls)->width ?
					(int)ft_strlen(obj->name) : (*ls)->width;
	(*ls)->w_links = ft_count_digits(obj->st_nlink, 10) > (*ls)->w_links ?
					ft_count_digits(obj->st_nlink, 10) : (*ls)->w_links;
	(*ls)->w_uid = (int)ft_strlen(obj->st_uid) > (*ls)->w_uid ?
					(int)ft_strlen(obj->st_uid) : (*ls)->w_uid;
	(*ls)->w_gid = (int)ft_strlen(obj->st_gid) > (*ls)->w_gid ?
					(int)ft_strlen(obj->st_gid) : (*ls)->w_gid;
	(*ls)->w_size = ft_count_digits(obj->st_size, 10) > (*ls)->w_size ?
					ft_count_digits(obj->st_size, 10) : (*ls)->w_size;
}

/*
** 		Read contents of a directory to a linked list
*/

void			read_dir(t_ls **ls, t_obj **head, char *dirname)
{
	struct dirent			*dp;
	t_obj					*obj;
	DIR						*dir;

	!(dir = opendir(dirname)) ? errors(dirname, 2) : PASS;
	if (dir)
	{
		while ((dp = readdir(dir)))
		{
			if ((*dp).d_name[0] == '.')
				continue ;
			obj = new_obj(dirname, (*dp).d_name);
			addlst(head, obj);
			(*ls)->objs++;
			calc_paddings(ls, obj);
		}
		dir ? closedir(dir) : PASS;
	}
}

/*
** 		Read contents of a directory to a linked list (including hidden files)
*/

void			read_dir_a(t_ls **ls, t_obj **head, char *dirname)
{
	struct dirent			*dp;
	t_obj					*obj;
	DIR						*dir;

	!(dir = opendir(dirname)) ? errors(dirname, 2) : PASS;
	if (dir)
	{
		while ((dp = readdir(dir)))
		{
			obj = new_obj(dirname, (*dp).d_name);
			addlst(head, obj);
			(*ls)->objs++;
			calc_paddings(ls, obj);
		}
		dir ? closedir(dir) : PASS;
	}
}
