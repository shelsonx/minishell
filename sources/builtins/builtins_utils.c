/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:55:23 by progerio          #+#    #+#             */
/*   Updated: 2023/03/08 16:47:45 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_amount_builtins(t_parser *parser_data)
{
	t_node	*current;
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

void	free_ft_exit(t_data *data)
{
	free_hashtable(data->parser_data->table_redirection);
	ft_free_nodes_env(&data->builtin_vars->env2);
	ft_free_nodes_env(&data->parser_data->commands);
	free(data->parser_data->tokenizer->content);
	free(data->parser_data->tokenizer->characters);
	free(data->parser_data->current_token);
	free(data->parser_data->tokenizer);
	free(data->parser_data->prompt->line);
	free(data->parser_data->prompt->prompt_str);
	free(data->parser_data->prompt->pwd);
	rl_clear_history();
	ft_free_fds(data->fds);
}

void	trated_builtin(t_data *data, int fd_out, char **input_cmd, int last)
{
	if (fd_out == INVALID_FD)
	{
		*data->exit_status = 1;
		return ;
	}
	free(*input_cmd);
	handler_builtins(data);
	if (last || data->parser_data->index == 1)
		*data->exit_status = 0;
	return ;
}
