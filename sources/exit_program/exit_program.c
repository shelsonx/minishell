#include "../../includes/minishell.h"

void	error_command_msg(char **args, char *input_cmd)
{
	char	*msg;
	char	*tmp;

	if (args[0] == NULL)
	{
		tmp = ft_strjoin("minishell: ", input_cmd);
		msg = ft_strjoin(tmp, ": command not found\n");
		write(STDOUT_FILENO, msg, ft_strlen(msg));
		free(tmp);
		free(msg);
	}
}

void	exit_program(t_data *data)
{
	ft_close_fds(data->fds);
	ft_free_tab(data->pipeline);
	ft_free_fds(data->fds);
}

void	ft_free_nodes(t_node **lst)
{
	t_node	*next;

	if (!lst)
		return ;
	next = *lst;
	while (next)
	{
		next = next->next;
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
}

void	free_children(t_parser *parser_data, char **redirection)
{
	free_parser_error(parser_data);
	ft_close_fds(parser_data->data->fds);
	ft_free_fds(parser_data->data->fds);
	ft_free_tab(parser_data->data->pipeline);
	ft_free_tab(redirection);
	free(parser_data->current_token);
	free(parser_data->tokenizer);
	ft_free_nodes_env(&parser_data->commands);
	ft_free_nodes_env(&parser_data->builtin_vars->env2);
	rl_clear_history();
}

void	free_children_main(t_data *data, char **env)
{
	free(data->parser_data->tokenizer->characteres);
	free(data->parser_data->prompt->line);
	free(data->parser_data->prompt->prompt_str);
	free(data->parser_data->prompt->pwd);
	free(data->parser_data->tokenizer->content);
	free(data->parser_data->current_token);
	free(data->parser_data->tokenizer);
	ft_free_nodes_env(&data->parser_data->commands);
	ft_free_nodes_env(&data->builtin_vars->env2);
	ft_free_tab(data->pipeline);
	ft_free_fds(data->fds);
	free_hashtable(data->parser_data->table_redirection);
	rl_clear_history();
	ft_free_tab(env);
}
