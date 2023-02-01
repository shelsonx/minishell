/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shelson <shelson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 20:14:17 by sjhony-x          #+#    #+#             */
/*   Updated: 2023/02/01 04:40:26 by shelson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*ft_last(t_node *lst)
{
	if (!lst)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_add_back(t_node **lst, t_node *new_node)
{
	t_node	*last;

	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	last = ft_last(*lst);
	last->next = new_node;
}

void	ft_add_front(t_node **lst, t_node *new_node)
{
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	new_node->next = *lst;
	*lst = new_node;
}

int	ft_size(t_node *lst)
{
	int		count;
	t_node	*tmp;

	if (!lst)
		return (0);
	count = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

t_node	*ft_new(int index, char	*value)
{
	t_node	*node;

	node = (t_node *) malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->index = index;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	ft_free_nodes(t_node **lst)
{
	t_node	*next;

	if (!lst)
		return ;
	next = *lst;
	while (next)
	{
		next = next->next;
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
}