#include "../../includes/minishell.h"

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

static char	*set_case_dir(char *exec_command, char *arg, char **paths)
{
	if (ft_strcmp(arg, "") != 0)
		msg_error("minishell: ", arg, ": Is a directory", 126);
	else
		msg_error("", "", "", 0);
	ft_free_tab(paths);
	exec_command = NULL;
	return (exec_command);
}

char	*get_exec_command(char *arg, t_builtin_vars *builtins)
{
	char	*exec_command;
	char	**paths;

	paths = get_paths(builtins);
	builtins->i = -1;
	while (paths[++builtins->i])
	{
		if (is_dir(arg) || (ft_strcmp(arg, "") == 0))
			return (set_case_dir(exec_command, arg, paths));
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
