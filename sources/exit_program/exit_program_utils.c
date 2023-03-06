#include "../../includes/minishell.h"

static int	is_dir_2(char *arg)
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

void	error_command_msg(char **args, char *input_cmd)
{
	char	*msg;
	char	*tmp;
	int		fd;

	if (args[0] == NULL && !is_dir_2(input_cmd)
		&& (ft_strcmp(input_cmd, "") != 0))
	{
		tmp = ft_strjoin("minishell: ", input_cmd);
		if (input_cmd[0] == '.' || input_cmd[0] == '/')
		{
			fd = open(input_cmd, O_RDONLY);
			if (fd == -1)
			{
				perror("minishell: ");
			}
			msg = NULL;
		}
		else
		{
			msg = ft_strjoin(tmp, ": command not found\n");
			write(STDERR_FILENO, msg, ft_strlen(msg));
		}
		free(tmp);
		free(msg);
	}
}

void	wait_all_pids(t_parser *parser_data, int total_commands)
{
	int	i;
	int	total_builtins;
	int	status;

	total_builtins = get_amount_builtins(parser_data);
	i = -1;
	status = -2;
	while (i++ < (total_commands - total_builtins))
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			*parser_data->data->exit_status = WEXITSTATUS(status);
		if (status == 256)
			*parser_data->data->exit_status = 1;
	}
	if (status == 512)
		*parser_data->data->exit_status = 1;
	if (parser_data->index > 1
		&& ft_strcmp(parser_data->commands->value, "export") == 0)
		*parser_data->data->exit_status = 1;
}
