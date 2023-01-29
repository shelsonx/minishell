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

int set_exec_command(char **exec_command, char *arg, char **paths, int i)
{
    if (ft_strncmp("./", arg, 2) == 0)
        *exec_command = ft_substr(arg, 2, ft_strlen(arg));
    else if (!is_full_path(arg))
        *exec_command = join_path_command(paths[i], arg);
    else
        *exec_command = ft_strdup(arg);
    if (access(*exec_command, X_OK) == 0)
    {
        ft_free_tab(paths);
		free(*exec_command);
        return (TRUE);
    }
    return (FALSE);
}

int	get_exit_status(char *arg)
{
	char	*exec_command;
	char	**paths;
	int		i;

	paths = get_paths_cmds(getenv("PATH"));
	i = 0;
	exec_command = NULL;
	while (paths[i])
	{
		if (set_exec_command(&exec_command, arg, paths, i))
            return (0);
		else
		{
			free(exec_command);
			exec_command = NULL;
		}
		i++;
	}
	set_exec_command(&exec_command, arg, paths, i-1);
	ft_free_tab(paths);
	if (access(exec_command, F_OK) == 0)
	{
		free(exec_command);
		return (126);
	}
	free(exec_command);
	return (127);
}

char	*get_exec_command(char *arg)
{
	char	*exec_command;
	char	**paths;
	int		i;

	paths = get_paths_cmds(getenv("PATH"));
	i = 0;
	while (paths[i])
	{
		if (ft_strncmp("./", arg, 2) == 0)
			exec_command = ft_substr(arg, 2, ft_strlen(arg));
		else if (!is_full_path(arg))
			exec_command = join_path_command(paths[i], arg);
		else
			exec_command = ft_strdup(arg);
		if (access(exec_command, X_OK) == 0)
		{
			ft_free_tab(paths);
			return (exec_command);
		}
		free(exec_command);
		exec_command = NULL;
		i++;
	}
	ft_free_tab(paths);
	return (NULL);
}
