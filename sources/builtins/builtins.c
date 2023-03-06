#include "../../includes/minishell.h"

char	**get_builtins_names(void)
{
	char	*names;

	names = "echo cd pwd export unset env exit";
	return (ft_split(names, ' '));
}

int	is_builtins(char *builtin_name)
{
	char	**names;
	int		i;

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

int	handler_builtins(t_data *data)
{
	int	fd_in;
	int	fd_out;

	save_fd(data, &fd_in, &fd_out);
	if (ft_strcmp(data->pipeline[0], "cd") == 0)
		exec_cd(data);
	if (ft_strcmp(data->pipeline[0], "export") == 0)
		exec_export(data);
	if (ft_strcmp(data->pipeline[0], "unset") == 0)
		exec_unset(data);
	if (ft_strcmp(data->pipeline[0], "pwd") == 0)
		exec_pwd(data);
	if (ft_strcmp(data->pipeline[0], "echo") == 0)
		ft_echo(data->pipeline);
	if (ft_strcmp(data->pipeline[0], "env") == 0)
		exec_env(data);
	if (ft_strcmp(data->pipeline[0], "exit") == 0)
	{
		free_ft_exit(data);
		ft_exit(data->pipeline);
	}
	restore_fd(data, &fd_in, &fd_out);
	return (1);
}
