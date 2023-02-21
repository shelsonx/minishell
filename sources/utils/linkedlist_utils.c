#include "../../includes/minishell.h"

t_linkedlist	*allocate_list(void)
{
	t_linkedlist	*list;

	list = (t_linkedlist *) ft_calloc (1, sizeof(t_linkedlist));
	return (list);
}

t_linkedlist	*linkedlist_insert(t_linkedlist *list, t_htitem *item)
{
	t_linkedlist	*head;
	t_linkedlist	*node;
	t_linkedlist	*temp;

	if (!list)
	{
		head = allocate_list();
		head->item = item;
		head->next = NULL;
		list = head;
		return (list);
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
