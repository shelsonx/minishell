/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:02:27 by progerio          #+#    #+#             */
/*   Updated: 2023/03/07 17:02:29 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_node	*swap_node(t_node *node_p1, t_node *node_p2)
{
	t_node		*tmp;

	tmp = node_p2->next;
	node_p2->next = node_p1;
	node_p1->next = tmp;
	return (node_p2);
}

t_node	**swap(t_node **current, int *swapped)
{
	t_node	*ptr_current;
	t_node	*ptr_next;

	ptr_current = *current;
	ptr_next = ptr_current->next;
	if (ft_toupper(ptr_current->value[0]) > ft_toupper(ptr_next->value[0]))
	{
		*current = swap_node(ptr_current, ptr_next);
		*swapped = TRUE;
	}
	current = &(*current)->next;
	return (current);
}

int	sort_queue(t_node **head, int count)
{
	t_node	**current;
	int		i;
	int		j;
	int		swapped;

	i = -1;
	while (++i <= count)
	{
		current = head;
		swapped = FALSE;
		j = -1;
		while (++j < count - i - 1)
			current = swap(current, &swapped);
		if (!swapped)
			break ;
	}
	return (0);
}
