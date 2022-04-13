/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 10:55:23 by abouchfa          #+#    #+#             */
/*   Updated: 2022/02/15 15:02:19 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// void	lst_swap(tlst_ingredient_info *a, tlst_ingredient_info *b)
// {
// 	int	tmp;

// 	tmp = a->data;
// 	a->data = b->data;
// 	b->data = tmp;
// }

tlst_ingredient_info	*lstlast(tlst_ingredient_info *stack)
{
	tlst_ingredient_info	*temp;

	if (!stack)
		return (stack);
	temp = stack;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	lstadd_back(tlst_ingredient_info **lst, tlst_ingredient_info *new)
{
	tlst_ingredient_info	*temp;

	if (!new)
		return ;
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	lstadd_front(tlst_ingredient_info **lst, tlst_ingredient_info *new)
{
	if (!new)
		return ;
	if (*lst)
		new->next = *lst;
	*lst = new;
}

void	ft_lstclear(tlst_ingredient_info **lst)
{
	tlst_ingredient_info	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		free(*lst);
		(*lst) = temp;
	}
}
