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

static int	is_dir(char *arg)
{
	struct stat	buffer;

	if (stat(arg, &buffer) != 0)
		return (FALSE);
	if (S_ISDIR(buffer.st_mode))
	{
		if (arg[0] == '.')
			arg++;
		if (arg[0] == '/')
			return (TRUE);
	}
	return (FALSE);
}

void	msg_error(char *msg1, char *msg2, char *msg3, int exit_status)
{
	char	*tmp;
	char	*tmp2;
	t_data	*data;

	data = *get_data();
	tmp = ft_strjoin(msg1, msg2);
	tmp2 = ft_strjoin(tmp, msg3);
	ft_putendl_fd(tmp2, STDERR_FILENO);
	free(tmp);
	free(tmp2);
	*data->exit_status = exit_status;
}

char	*get_exec_command(char *arg, t_builtin_vars *builtins)
{
	char	*exec_command;
	char	**paths;

	paths = get_paths(builtins);
	builtins->i = -1;
	while (paths[++builtins->i])
	{
		if (is_dir(arg))
		{
			msg_error("minishell: ", arg, ": Is a directory", 126);
			ft_free_tab(paths);
			exec_command = ft_strdup(arg);
			return exec_command;
		}
		if (ft_strncmp("./", arg, 2) == 0)
			exec_command = ft_substr(arg, 2, ft_strlen(arg));
		else if (!is_full_path(arg, builtins))
			exec_command = join_path_command(paths[builtins->i], arg);
		else
			exec_command = ft_strdup(arg);
		if (access(exec_command, X_OK) == 0)
		{
			ft_free_tab(paths);
			return (exec_command);
		}
		free(exec_command);
		exec_command = NULL;
	}
	ft_free_tab(paths);
	return (NULL);
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
