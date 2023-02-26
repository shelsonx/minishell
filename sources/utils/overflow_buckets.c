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
