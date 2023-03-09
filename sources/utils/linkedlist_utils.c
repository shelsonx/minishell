/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:02:11 by progerio          #+#    #+#             */
/*   Updated: 2023/03/07 17:02:13 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_linkedlist	*allocate_list(void)
{
	t_linkedlist	*list;

	list = (t_linkedlist *) ft_calloc (1, sizeof(t_linkedlist));
	return (list);
}

t_linkedlist	*linkedlist_insert_items(t_linkedlist *list, t_htitem *item)
{
	t_linkedlist	*head;

	head = allocate_list();
	head->item = item;
	head->next = NULL;
	list = head;
	return (list);
}

t_linkedlist	*linkedlist_insert(t_linkedlist *list, t_htitem *item)
{
	t_linkedlist	*node;
	t_linkedlist	*temp;

	if (!list)
	{
		linkedlist_insert_items(list, item);
	}
	else if (list->next == NULL)
	{
		node = allocate_list();
		node->item = item;
		node->next = NULL;
		list->next = node;
		return (list);
	}
	temp = list;
	while (temp->next)
	{
		temp = temp->next;
	}
	node = allocate_list();
	node->item = item;
	node->next = NULL;
	temp->next = node;
	return (list);
}

void	free_linkedlist(t_linkedlist *list)
{
	t_linkedlist	*temp;

	temp = list;
	if (!list)
		return ;
	while (list)
	{
		temp = list;
		list = list->next;
		free(temp->item->key);
		free(temp->item->value);
		free(temp->item);
		free(temp);
	}
}
