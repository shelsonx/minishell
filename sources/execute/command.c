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
		if (fd_out == INVALID_FD)
		{
			*data->exit_status = 1;
			return ;
		}
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
		if (data->args[0] == NULL || fd_in == INVALID_FD)
			return ;
		child_pid = execute_child_process(data);
		//waitpid(child_pid, &status, 0);
		if (waitpid(child_pid, &status, 0) == -1)
			perror("minishell: ");
		if ( WIFEXITED(status) ) {
			const int es = WEXITSTATUS(status);
			*data->exit_status = es;
			//dprintf(2, "exit status was %d\n", es);
		}
	}
}

static int	set_and_valid_args(t_data *data, char *input_cmd, int fd_out)
{
	data->args = create_args(data->pipeline, data->builtin_vars);
	error_command_msg(data->args, input_cmd);
	free(input_cmd);
	if (data->args[0] == NULL || fd_out == INVALID_FD)
		return (FALSE);
	else
		return (TRUE);
}

void	exec_first_command(t_data *data, int fd_in, int fd_out)
{
	char	*input_cmd;

	set_fds_first_cmd(data, fd_in, fd_out);
	input_cmd = ft_strdup(data->pipeline[0]);
	if (is_builtins(input_cmd))
	{
		free(input_cmd);
		handler_builtins(data);
		ft_free_tab(data->pipeline);
		data->pipeline = NULL;
		return ;
	}
	else
	{
		if (!set_and_valid_args(data, input_cmd, fd_out) || fd_in == INVALID_FD)
		{
			ft_free_tab(data->args);
			return ;
		}
		execute_child_process(data);
		ft_free_tab(data->args);
		data->args = NULL;
	}
}

void	exec_middles_commands(t_data *data,
		t_parser *parser_data, int total_cmds_middles)
{
	int		i;
	char	*input_cmd;

	i = 0;
	while (i < total_cmds_middles)
	{
		set_fds_middle_cmd(data, parser_data, i);
		data->pipeline = get_pipeline(data, parser_data, i + 1);
		expander(data->pipeline, parser_data->builtin_vars, data);
		remove_quotes(data->pipeline);
		input_cmd = ft_strdup(data->pipeline[0]);
		if (is_builtins(input_cmd))
		{
			free(input_cmd);
			handler_builtins(data);
			return ;
		}
		if (!set_and_valid_args(data, input_cmd, data->fd_out))
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
		if (fd_out == INVALID_FD)
		{
			*data->exit_status = 1;
			return ;
		}
		free(input_cmd);
		handler_builtins(data);
		return ;
	}
	*data->exit_status = get_exit_status(input_cmd, data->builtin_vars);
	data->args = create_args(data->pipeline, data->builtin_vars);
	error_command_msg(data->args, input_cmd);
	free(input_cmd);
	if (data->args[0] == NULL || fd_out == INVALID_FD)
		return ;
	else
		*data->exit_status = 0;
	execute_child_process(data);
}
