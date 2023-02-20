#include "../../includes/minishell.h"

char	*get_input_cmd(int position)
{
	char			*num_str;
	static char 	index_cmd[128];

	ft_memset(index_cmd, 0, 128);
	num_str = ft_itoa(position);
	ft_strcpy(index_cmd, num_str);
	free(num_str);
	return (index_cmd);
}

static	void exec_only_one_command(t_data *data, t_parser *parser_data)
{
	char	*index_cmd;
	int 	fd_in;
	int 	fd_out;

	index_cmd = get_input_cmd(0);
	if (has_redirect(parser_data, "<", index_cmd) && get_fd_in(parser_data, index_cmd) == -1)
		return ;
	data->pipeline = get_pipeline(data, parser_data, 0);
	expander(data->pipeline, parser_data->builtin_vars, data);
	remove_quotes(data->pipeline);
	fd_in = get_fd_in(parser_data, index_cmd);
	fd_out = get_fd_out(parser_data, index_cmd);
	exec_one_command(data, fd_in, fd_out);
}

static void exec_two_commands(t_data *data, t_parser *parser_data, int total_commands)
{
	char	*index_cmd;

	index_cmd = get_input_cmd(0);
	data->pipeline = get_pipeline(data, parser_data, 0);
	expander(data->pipeline, parser_data->builtin_vars, data);
	remove_quotes(data->pipeline);
	data->fds = create_pipes(1);
	exec_first_command(data, 
		get_fd_in(parser_data, index_cmd),
		get_fd_out(parser_data, index_cmd));
	data->pipeline = get_pipeline(data, parser_data, 1);
	expander(data->pipeline, parser_data->builtin_vars, data);
	remove_quotes(data->pipeline);
	index_cmd = get_input_cmd(1);
	int fd_in = get_fd_in(parser_data, index_cmd);
	if (fd_in == -1)
		fd_in = data->fds[0][0];
	index_cmd = get_input_cmd(total_commands -1);
	int out = get_fd_out(parser_data, index_cmd);
	exec_last_command(data, fd_in, out);
}

static void exec_serveral_commands(t_data *data, t_parser *parser_data, int total_commands)
{
	char	*index_cmd;

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
	int fd_in = get_fd_in(parser_data, index_cmd);
	if (fd_in == -1)
		fd_in = data->fds[total_commands -2][0];
	index_cmd = get_input_cmd(total_commands -1);
	exec_last_command(data, fd_in, get_fd_out(parser_data, index_cmd));
}

int	open_files(t_parser *parser_data)
{
	char *num_str;
	char name[128];
	ft_memset(name, 0, 128);
	num_str = ft_itoa(0);
	ft_strcpy(name, num_str);
	get_fd_in(parser_data, name);
	get_fd_out(parser_data, name);
	free(num_str);
	return (-1);
}

int execute(t_parser *parser_data)
{
	t_data		data;
	int			total_commands;
	int			total_builtins;
	static int	exit_status;
	int 		i;

	data.fds = NULL;
	data.pipeline = NULL;
	data.exit_status = &exit_status;
	data.builtin_vars = parser_data->builtin_vars;
	data.parser_data = parser_data;
	total_commands = parser_data->index;
	total_builtins = get_amount_builtins(parser_data);
	parser_data->data = &data;
	if (total_commands == 0)
		return open_files(parser_data);
	if (total_commands == 1)
		exec_only_one_command(&data, parser_data);
	if (total_commands == 2)
		exec_two_commands(&data, parser_data, total_commands);
	else if (total_commands > 2)
		exec_serveral_commands(&data, parser_data, total_commands);
	if (total_commands > 0)
		exit_program(&data);
	i = -1;
	while (i++ < (total_commands - total_builtins))
		waitpid(-1, NULL, 0);
    return (0);
}
