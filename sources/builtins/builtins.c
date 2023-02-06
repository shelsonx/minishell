#include "../../includes/minishell.h"

char    **get_builtins_names(void)
{
    char    *names;

    names = "echo cd pwd export unset env exit";
    return (ft_split(names, ' '));
}

int is_builtins(char *builtin_name)
{
    char    **names;
    int     i;

    names = get_builtins_names();
    i = -1;
    while (names[++i])
    {
        if (ft_strcmp(builtin_name, names[i]) == 0)
        {
            ft_free_tab(names);
            return (true);
        }
    }
    ft_free_tab(names);
    return (false);
}

static void	save_fd(t_data *data, int *fd_in, int *fd_out)
{
	*fd_in = dup(STDIN_FILENO);
	*fd_out = dup(STDOUT_FILENO);
	dup2(data->fd_out, STDOUT_FILENO);
    dup2(data->fd_in, STDIN_FILENO);
}

static void	restore_fd(t_data *data, int *fd_in, int *fd_out)
{
    if (data->fd_in != -1)
	    close(data->fd_in);
    if (data->fd_out != -1)
	    close(data->fd_out);
	dup2(*fd_in, STDIN_FILENO);
	dup2(*fd_out, STDOUT_FILENO);
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

int handler_builtins(t_data *data)
{
	int	fd_in;
	int	fd_out;
	save_fd(data, &fd_in, &fd_out);
    if (ft_strcmp(data->pipeline[0],"cd") == 0)
		ft_cd(data);
    if (ft_strcmp(data->pipeline[0],"export") == 0)
		ft_export(data->builtin_vars, data->pipeline);
     if (ft_strcmp(data->pipeline[0],"unset") == 0)
		ft_unset(data->builtin_vars, data->pipeline);
	if (ft_strcmp(data->pipeline[0],"pwd") == 0)
		ft_pwd(data->builtin_vars);
	if (ft_strcmp(data->pipeline[0],"echo") == 0)
		ft_echo(data->pipeline);
	if (ft_strcmp(data->pipeline[0],"env") == 0)
		ft_env(data->builtin_vars);
	if (ft_strcmp(data->pipeline[0], "exit") == 0)
	{
        free_ft_exit(data);
		ft_exit(data->pipeline);
	}
	restore_fd(data, &fd_in, &fd_out);
    return (1);
}
