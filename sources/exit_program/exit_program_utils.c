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
