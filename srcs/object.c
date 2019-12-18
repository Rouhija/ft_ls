/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:47:30 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/18 13:27:11 by srouhe           ###   ########.fr       */
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
		if (S_ISLNK(obj->st_mode))
			ft_strdel(&obj->link);
		free(obj);
		obj = NULL;
	}
	if (ls && *ls)
		reset_dir(ls);
}

/*
** 		Create new symlink object 
*/

t_obj			*new_symlink(char *path, char *filename)
{
	t_obj			*obj;
	struct stat 	attr;
	char			buf[LNKBUF];
	char 			*tmp;

	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		exit_program(2);
	lstat(path, &attr);
	ft_bzero(buf, LNKBUF);
	readlink(path, buf, LNKBUF);
	tmp = ft_strjoin(filename, " -> ");
	obj->link = ft_strjoin(tmp, buf);
	free(tmp);
	obj->st_mode = attr.st_mode;
	obj->path = path;
	obj->name = ft_strdup(filename);
	obj->rights = permissions_link((int)attr.st_mode);
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

/*
** 		Create new object 
*/

t_obj			*new_obj(char *dirname, char *filename)
{
	t_obj			*obj;
	struct stat 	attr;
	struct stat 	links;
	char			*path;

	path = pathjoin(dirname, filename);
	lstat(path, &links);
	if (S_ISLNK(links.st_mode))
		return (new_symlink(path, filename));
	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		exit_program(2);
	stat(path, &attr);
	obj->path = path;
	obj->st_mode = attr.st_mode;
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
