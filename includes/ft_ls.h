/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 16:58:46 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/17 14:50:10 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** -------- HEADERS --------
*/

# include "libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <stdio.h>
# include <string.h>
# include <pwd.h>
# include <grp.h>
// # include <uuid/uuid.h>
# include <time.h>
# include <sys/ioctl.h>

/*
** -------- MACROS --------
*/

# define LLIST		(1 << 0)
# define RECURSE	(1 << 1)
# define HIDDEN		(1 << 2)
# define RSORT		(1 << 3)
# define TSORT		(1 << 4)
# define NUL		(1 >> 1)

/*
** -------- TYPEDEFS --------
*/

# define OPTIONS "Ralrt"

# ifndef TIOCGSIZE
#  define TIOCGSIZE TIOCGWINSZ
# endif

typedef struct		s_obj
{
	mode_t			st_mode;
	char			*path;
	char			*name;
	char			*rights;
	nlink_t			st_nlink;
	char			*st_uid;
	off_t			st_size;
	char			*dt;
	time_t			st_time;
	quad_t			st_blocks;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	t_obj			*item;
}					t_btree;

typedef struct		s_ls
{
	size_t			width;
	size_t			total;
	short			flags;
	char			*dirname;
	int				objs;
}					t_ls;

/*
** -------- FUNCTIONS --------
*/

void				object_del(t_obj **head, t_ls **ls);
void				print_obj_long(t_obj **head, t_ls **ls);
void				print_obj_short(t_obj **head, t_ls **ls);
void				exit_program(int reason);
void				ft_ls(t_ls **ls);
void				read_dir_rev(t_ls **ls, t_btree **btree, char *dirname);
t_obj				*new_obj(char *name, char *path);
char				*pathjoin(char *dirname, char *filename);
char				*permissions(int st_mode);

char				*datestring(char *dt);

void				print_lst(t_list *lst);
DIR					*open_dir(char *dir);

t_btree				*btree_new(t_obj **item);
char				*btree_search_dir(t_btree *root, int i, int j);
void 				btree_del(t_btree *node);
void				btree_insert(t_btree **root, t_obj **item);
void				btree_insert_rev(t_btree **root, t_obj **item);
void				btree_insert_time(t_btree **root, t_obj **item);
void				btree_apply_infix(t_btree *root, t_ls **ls, void (*applyf)(t_obj *, t_ls **));
void				btree_apply_infix_rev(t_btree *root, t_ls **ls, void (*applyf)(t_obj *, t_ls **));

void			read_dir(t_ls **ls, t_obj **head, char *dirname);
void			read_dir_a(t_ls **ls, t_obj **head, char *dirname);
void	addlst(t_obj **alst, t_obj *new);
void	objiter(t_obj **lst, t_ls **ls, void (*applyf)(t_obj **, t_ls **));
char    *lst_search(t_obj *lst, int i, int index);
void			recurse_dirs(t_ls **ls, char *dirname);
void			merge_sort(t_obj **headref, t_ls **ls);

#endif
