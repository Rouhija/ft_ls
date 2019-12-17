/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:47:30 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/17 18:21:24 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** 		Delete and free object
*/

void		object_del(t_obj **head, t_ls **ls)
{
	t_obj *obj;

	obj = *head;
	if (obj)
	{
		ft_strdel(&obj->path);
		ft_strdel(&obj->name);
		ft_strdel(&obj->rights);
		ft_strdel(&obj->st_uid);
		ft_strdel(&obj->st_gid);
		ft_strdel(&obj->dt);
		free(obj);
		obj = NULL;
	}
	if (ls && *ls)
	{
		(*ls)->width = 0;
		(*ls)->total = 0;
		(*ls)->objs = 0;		
	}
}

/*
** 		Create new object 
*/

t_obj			*new_obj(char *dirname, char *filename)
{
	t_obj			*obj;
	struct stat 	attr;

	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		exit_program(2);
	obj->st_mode = attr.st_mode;
	obj->path = pathjoin(dirname, filename);
	stat(obj->path, &attr);
	obj->name = ft_strdup(filename);
	obj->rights = permissions((int)attr.st_mode);
	obj->st_nlink = attr.st_nlink;
	obj->st_uid = ft_strdup(getpwuid(attr.st_uid)->pw_name);
	obj->st_gid = ft_strdup(getgrgid(attr.st_gid)->gr_name);
	obj->st_size = attr.st_size;
	obj->dt = ft_strdup(&(ctime(&attr.st_mtime)[4]));
	obj->st_time = attr.st_mtime;
	obj->st_blocks = attr.st_blocks;
	obj->next = NULL;
	return (obj);
}
