#include "../../includes/minishell.h"

char	*get_input_cmd(int position)
{
	char			*num_str;
	static char		index_cmd[128];

	ft_memset(index_cmd, 0, 128);
	num_str = ft_itoa(position);
	ft_strcpy(index_cmd, num_str);
	free(num_str);
	return (index_cmd);
}

void	exec_only_one_command(t_data *data, t_parser *parser_data)
{
	char	*index_cmd;
	int		fd_in;
	int		fd_out;

	data->pipeline = get_pipeline(data, parser_data, 0);
	index_cmd = get_input_cmd(0);
	if (ft_strcmp(data->pipeline[0], "echo") != 0)
		fd_in = get_fd_in(parser_data, index_cmd);
	if (has_redirect(parser_data, "<", index_cmd)
		&& fd_in == -1)
		{
			*data->exit_status = 1;
			return ;
		}
	if (fd_in == INVALID_FD)
	{
		*data->exit_status = 1;
		return ;
	}
	expander(data->pipeline, parser_data->builtin_vars, data);
	remove_quotes(data->pipeline);
	//fd_in = get_fd_in(parser_data, index_cmd);
	fd_out = get_fd_out(parser_data, index_cmd);
	if (fd_out == INVALID_FD)
		return ;
	exec_one_command(data, fd_in, fd_out);
}

void	exec_two_commands(t_data *data,
	t_parser *parser_data, int total_commands)
{
	char	*index_cmd;
	int		fd_in;
	int		fd_out;

	index_cmd = get_input_cmd(0);
	data->pipeline = get_pipeline(data, parser_data, 0);
	expander(data->pipeline, parser_data->builtin_vars, data);
	remove_quotes(data->pipeline);
	data->fds = create_pipes(1);
	fd_in = get_fd_in(parser_data, index_cmd);
	fd_out = get_fd_out(parser_data, index_cmd);
	exec_first_command(data, fd_in, fd_out);
	data->pipeline = get_pipeline(data, parser_data, 1);
	expander(data->pipeline, parser_data->builtin_vars, data);
	remove_quotes(data->pipeline);
	index_cmd = get_input_cmd(1);
	fd_in = get_fd_in(parser_data, index_cmd);
	if (fd_in == -1)
		fd_in = data->fds[0][0];
	index_cmd = get_input_cmd(total_commands -1);
	fd_out = get_fd_out(parser_data, index_cmd);
	exec_last_command(data, fd_in, fd_out);
}

void	exec_serveral_commands(t_data *data,
		t_parser *parser_data, int total_commands)
{
	char	*index_cmd;
	int		fd_in;

	data->pipeline = get_pipeline(data, parser_data, 0);
	expander(data->pipeline, parser_data->builtin_vars, data);
	remove_quotes(data->pipeline);
	data->fds = create_pipes(total_commands -1);
	index_cmd = get_input_cmd(0);
	exec_first_command(data,
		get_fd_in(parser_data, index_cmd),
		get_fd_out(parser_data, index_cmd));
	exec_middles_commands(data, parser_data, total_commands -2);
	ft_free_tab(data->pipeline);
	data->pipeline = NULL;
	data->pipeline = get_pipeline(data, parser_data, total_commands -1);
	expander(data->pipeline, parser_data->builtin_vars, data);
	remove_quotes(data->pipeline);
	index_cmd = get_input_cmd(total_commands -1);
	fd_in = get_fd_in(parser_data, index_cmd);
	if (fd_in == -1)
		fd_in = data->fds[total_commands -2][0];
	index_cmd = get_input_cmd(total_commands -1);
	exec_last_command(data, fd_in, get_fd_out(parser_data, index_cmd));
}

int	execute(t_parser *parser_data)
{
	t_data		data;
	int			total_commands;
	int			total_builtins;
	static int	exit_status;
	int			i;
	int			status;

	status = -2;
	data.fds = NULL;
	data.pipeline = NULL;
	data.exit_status = &exit_status;
	data.builtin_vars = parser_data->builtin_vars;
	data.parser_data = parser_data;
	total_commands = parser_data->index;
	total_builtins = get_amount_builtins(parser_data);
	parser_data->data = &data;
	set_data(&data);
	handler_cmds(&data, parser_data, total_commands);
	if (total_commands > 0)
		exit_program(&data);
	i = -1;
	while (i++ < (total_commands - total_builtins))
	{

		waitpid(-1, &status, 0);
		if ( WIFEXITED(status) ) {
			const int es = WEXITSTATUS(status);
			*parser_data->data->exit_status = es;
		}
		if (status == 256)
			*parser_data->data->exit_status = 1;
		//dprintf(2, "status =%d\n", status);
	}
	return (0);
}
