/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:01:48 by progerio          #+#    #+#             */
/*   Updated: 2023/03/07 17:01:50 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_hashtable	*create_table(int size)
{
	int				i;
	t_hashtable		*table;

	table = (t_hashtable *) malloc (sizeof(t_hashtable));
	table->size = size;
	table->count = 0;
	table->items = (t_htitem **) ft_calloc (table->size, sizeof(t_htitem *));
	i = 0;
	while (i < table->size)
	{
		table->items[i] = NULL;
		i++;
	}
	table->overflow_buckets = create_overflow_buckets(table);
	return (table);
}

void	ht_insert_items(t_hashtable *table,
			t_htitem *item, int index, char *value)
{
	free(table->items[index]->value);
	table->items[index]->value = (char *) ft_calloc (
			ft_strlen(value) + 1, sizeof(char));
	ft_strcpy(table->items[index]->value, value);
	free_item(item);
}

void	ht_insert_current_items(t_hashtable *table, t_htitem *item, int index)
{
	if (table->count == table->size)
	{
		printf("Insert Error: Hash Table is full\n");
		free_item(item);
		return ;
	}
	table->items[index] = item;
	table->count++;
}

void	ht_insert(t_hashtable *table, char *key, char *value)
{
	t_htitem	*item;
	int			index;
	t_htitem	*current_item;

	item = create_item(key, value);
	index = hash_function(key);
	current_item = table->items[index];
	if (current_item == NULL)
	{
		ht_insert_current_items(table, item, index);
	}
	else
	{
		if (ft_strcmp(current_item->key, key) == 0)
		{
			ht_insert_items(table, item, index, value);
			return ;
		}
		else
		{
			handle_collision(table, index, item);
			return ;
		}
	}
}

char	*ht_search(t_hashtable *table, char *key)
{
	int				index;
	t_htitem		*item;
	t_linkedlist	*head;

	index = hash_function(key);
	item = table->items[index];
	head = table->overflow_buckets[index];
	while (item != NULL)
	{
		if (ft_strcmp(item->key, key) == 0)
			return (item->value);
		if (head == NULL)
			return (NULL);
		item = head->item;
		head = head->next;
	}
	return (NULL);
}
