#include "../../includes/minishell.h"

void	exec_one_command(t_data *data, int fd_in, int fd_out)
{
	pid_t	child_pid;
	int		status;
	char	*input_cmd;
	
	data->fd_in = fd_in;
	data->fd_out = fd_out;
	input_cmd = ft_strdup(data->pipeline[0]);
	data->fds = create_pipes(1);
	if (is_builtins(input_cmd))
	{
		free(input_cmd);
		handler_builtins(data);
		return ;
	}
	else
	{
		*data->exit_status = get_exit_status(input_cmd, data->builtin_vars);
		data->args = create_args(data->pipeline, data->builtin_vars);
		error_command_msg(data->args, input_cmd);
		free(input_cmd);
		if (data->args[0] == NULL)
			return ;
		child_pid = execute_child_process(data);
		waitpid(child_pid, &status, 0);
	}
}

void	exec_first_command(t_data *data, int fd_in, int fd_out)
{
	char	*input_cmd;

	data->fd_in = fd_in;
	if (fd_out == -1)
		data->fd_out = data->fds[0][1];
	else
		data->fd_out = fd_out;
	input_cmd = ft_strdup(data->pipeline[0]);
	if (is_builtins(input_cmd))
	{
		free(input_cmd);
		handler_builtins(data);
		return ;
	}
	else
	{
		data->args = create_args(data->pipeline, data->builtin_vars);
		error_command_msg(data->args, input_cmd);
		free(input_cmd);
		if (data->args[0] == NULL)
		{
			ft_free_tab(data->pipeline);
			return ;
		}
		execute_child_process(data);
		ft_free_tab(data->args);
		data->args = NULL;
	}
}

void set_fds(t_data *data, t_parser *parser_data, int i)
{

	int		fd_in;
	int		fd_out;
	char	*index_cmd;

	index_cmd = get_input_cmd(i+1);
	fd_in = get_fd_in(parser_data, index_cmd); 
	fd_out = get_fd_out(parser_data, index_cmd);
	if (fd_in == -1) 
		data->fd_in = data->fds[i][0];
	else
		data->fd_in = fd_in;
	if (fd_out == -1)
		data->fd_out = data->fds[i+1][1];
	else
		data->fd_out = fd_out;
}

void	exec_middles_commands(t_data *data, t_parser *parser_data, int total_cmds_middles)
{
	int		i;
	char	*input_cmd;

	i = 0;
	while (i < total_cmds_middles)
	{
		set_fds(data, parser_data, i);
		data->pipeline = get_pipeline(data, parser_data, i+1);
		expander(data->pipeline, parser_data->builtin_vars, data);
		remove_quotes(data->pipeline);
		input_cmd = ft_strdup(data->pipeline[0]);
		if (is_builtins(input_cmd))
		{
			free(input_cmd);
			handler_builtins(data);
			return ;
		}
		data->args = create_args(data->pipeline, data->builtin_vars);
		error_command_msg(data->args, input_cmd);
		free(input_cmd);
		if (data->args[0] == NULL)
			return ;
		execute_child_process(data);
		ft_free_tab(data->pipeline);
		data->pipeline = NULL;
		i++;
	}
}

void	exec_last_command(t_data *data, int fd_in, int fd_out)
{
	char	*input_cmd;

	data->fd_in = fd_in;
	if (fd_out == -1)
		data->fd_out = STDOUT_FILENO;
	else
		data->fd_out = fd_out;
	input_cmd = ft_strdup(data->pipeline[0]);
	if (is_builtins(input_cmd))
	{
		free(input_cmd);
		handler_builtins(data);
		return ;
	}
	*data->exit_status = get_exit_status(input_cmd, data->builtin_vars);
	data->args = create_args(data->pipeline, data->builtin_vars);
	error_command_msg(data->args, input_cmd);
	free(input_cmd);
	if (data->args[0] == NULL)
		return ;
	else
		*data->exit_status = 0;
	execute_child_process(data);
}
