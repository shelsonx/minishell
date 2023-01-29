#include "../../includes/minishell.h"

int get_amount_builtins(t_parser *parser_data)
{
    t_node  *current;
	int		amount;

    current = parser_data->commands;
	amount = 0;
    while (current)
    {
		if (is_builtins(current->value))
			amount++;
        current = current->next;
    }
	return (amount);
}
