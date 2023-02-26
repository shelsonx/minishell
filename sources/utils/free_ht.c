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
