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

void    free_ft_exit(t_data *data)
{
    free_hashtable(data->parser_data->table_redirection);
    ft_free_nodes_env(&data->builtin_vars->env2);
    ft_free_nodes_env(&data->parser_data->commands);
    free(data->parser_data->tokenizer->content);
    free(data->parser_data->tokenizer->characteres);
    free(data->parser_data->current_token);
    free(data->parser_data->tokenizer);
    free(data->parser_data->prompt->line);
    free(data->parser_data->prompt->prompt_str);
    free(data->parser_data->prompt->pwd);
    rl_clear_history();
    ft_free_fds(data->fds);
}