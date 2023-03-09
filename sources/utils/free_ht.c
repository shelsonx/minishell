/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ht.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:01:32 by progerio          #+#    #+#             */
/*   Updated: 2023/03/07 17:01:34 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_hashtable(t_hashtable *table)
{
	int			i;
	t_htitem	*item;

	i = 0;
	while (i < table->size)
	{
		item = table->items[i];
		if (item != NULL)
			free_item(item);
		i++;
	}
	free_overflow_buckets(table);
	free(table->items);
	free(table);
}
