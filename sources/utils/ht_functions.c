#include "../../includes/minishell.h"

unsigned long	hash_function(char *str)
{
	unsigned long	i;
	int				j;

	i = 0;
	j = 0;
	while (str[j])
	{
		i += str[j];
		j++;
	}
	return (i % CAPACITY);
}

t_htitem	*create_item(char *key, char *value)
{
	t_htitem	*item;

	item = (t_htitem *) malloc (sizeof(t_htitem));
	item->key = (char *) ft_calloc (ft_strlen(key) + 1, sizeof(char));
	item->value = (char *) ft_calloc (ft_strlen(value) + 1, sizeof(char));
	ft_strcpy(item->key, key);
	ft_strcpy(item->value, value);
	return (item);
}

void	free_item(t_htitem *item)
{
	free(item->key);
	free(item->value);
	free(item);
}

void	handle_collision(t_hashtable *table,
			unsigned long index, t_htitem *item)
{
	t_linkedlist	*head;

	head = table->overflow_buckets[index];
	if (head == NULL)
	{
		head = allocate_list();
		head->item = item;
		table->overflow_buckets[index] = head;
		return ;
	}
	else
	{
		table->overflow_buckets[index] = linkedlist_insert(head, item);
		return ;
	}
}
