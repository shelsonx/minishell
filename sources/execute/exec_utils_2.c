#include "../../includes/minishell.h"

void	open_files(t_parser *parser_data)
{
	char	*num_str;
	char	name[128];

	ft_memset(name, 0, 128);
	num_str = ft_itoa(0);
	ft_strcpy(name, num_str);
	get_fd_in(parser_data, name);
	get_fd_out(parser_data, name);
	free(num_str);
}

void	handler_cmds(t_data *data, t_parser *parser_data, int total_commands)
{
	if (total_commands == 0)
		return (open_files(parser_data));
	if (total_commands == 1)
		exec_only_one_command(data, parser_data);
	if (total_commands == 2)
		exec_two_commands(data, parser_data, total_commands);
	else if (total_commands > 2)
		exec_serveral_commands(data, parser_data, total_commands);
}

t_data	**get_data(void)
{
	static t_data	*data;

	return (&data);
}

void	set_data(t_data *data)
{
	t_data	**data_save;

	data_save = get_data();
	*data_save = data;
}
