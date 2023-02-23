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
