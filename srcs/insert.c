/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srouhe <srouhe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 14:30:23 by srouhe            #+#    #+#             */
/*   Updated: 2019/12/17 11:49:13 by srouhe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** 		Insert values to binary tree in ascending ascii order
*/

void		btree_insert(t_btree **root, t_obj **item)
{
	t_obj	*tmp;

	if (*root == NULL || (*root)->item == NULL)
	{
		*root = btree_new(item);
		return ;
	}
	tmp = (*root)->item;
	if (ft_strcmp((*item)->name, tmp->name) < 0)
	{
		if ((*root)->left)
			btree_insert(&((*root)->left), item);
		else
			(*root)->left = btree_new(item);
	}
	else
	{
		if ((*root)->right)
			btree_insert(&((*root)->right), item);
		else
			(*root)->right = btree_new(item);
	}
}

/*
** 		Insert values to binary tree in descending ascii order
*/

void		btree_insert_rev(t_btree **root, t_obj **item)
{
	t_obj	*tmp;

	if (*root == NULL || (*root)->item == NULL)
	{
		*root = btree_new(item);
		return ;
	}
	tmp = (*root)->item;
	if (ft_strcmp((*item)->name, tmp->name) > 0)
	{
		if ((*root)->left)
			btree_insert_rev(&((*root)->left), item);
		else
			(*root)->left = btree_new(item);
	}
	else
	{
		if ((*root)->right)
			btree_insert_rev(&((*root)->right), item);
		else
			(*root)->right = btree_new(item);
	}
}

/*
** 		Insert values to binary tree sorted by last modified time
*/

void		btree_insert_time(t_btree **root, t_obj **item)
{
	t_obj	*tmp;

	if (*root == NULL || (*root)->item == NULL)
	{
		*root = btree_new(item);
		return ;
	}
	tmp = (*root)->item;
	if ((*item)->st_time > tmp->st_time)
	{
		if ((*root)->left)
			btree_insert_time(&((*root)->left), item);
		else
			(*root)->left = btree_new(item);
	}
	else
	{
		if ((*root)->right)
			btree_insert_time(&((*root)->right), item);
		else
			(*root)->right = btree_new(item);
	}
}