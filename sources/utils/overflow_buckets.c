/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overflow_buckets.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:02:18 by progerio          #+#    #+#             */
/*   Updated: 2023/03/07 17:02:20 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_linkedlist	**create_overflow_buckets(t_hashtable *table)
{
	int				i;
	t_linkedlist	**buckets;

	buckets = (t_linkedlist **) ft_calloc (table->size, sizeof(t_linkedlist *));
	i = 0;
	while (i < table->size)
	{
		buckets[i] = NULL;
		i++;
	}
	return (buckets);
}

void	free_overflow_buckets(t_hashtable *table)
{
	int				i;
	t_linkedlist	**buckets;

	buckets = table->overflow_buckets;
	i = 0;
	while (i < table->size)
	{
		free_linkedlist(buckets[i]);
		i++;
	}
	free(buckets);
}
