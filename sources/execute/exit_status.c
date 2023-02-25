#include "../../includes/minishell.h"

static int	set_exec_command(char **exec_command, char *arg,
		char **paths, t_builtin_vars *builtins)
{
	if (ft_strncmp("./", arg, 2) == 0)
		*exec_command = ft_substr(arg, 2, ft_strlen(arg));
	else if (!is_full_path(arg, builtins))
		*exec_command = join_path_command(paths[builtins->i], arg);
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

static int	set_exec_cmds(char **exec_command, char *arg,
		char **paths, t_builtin_vars *builtins)
{
	if (set_exec_command(exec_command, arg, paths, builtins))
		return (0);
	else
	{
		free(*exec_command);
		exec_command = NULL;
	}
	return (-1);
}

static int	has_permission(char *exec_command)
{
	if (access(exec_command, F_OK) == 0)
	{
		free(exec_command);
		return (FALSE);
	}
	free(exec_command);
	return (TRUE);
}

static int	get_status(char **exec_command, char *arg,
		char **paths, t_builtin_vars *builtins)
{
	set_exec_command(exec_command, arg, paths, builtins);
	ft_free_tab(paths);
	if (!has_permission(*exec_command))
		return (126);
	return (127);
}

int	get_exit_status(char *arg, t_builtin_vars *builtins)
{
	char	*exec_command;
	char	**paths;
	char	*env_path;
	int		i;

	env_path = get_env_path("PATH", builtins);
	if (ft_strcmp(env_path, "") == 0)
	{
		free(env_path);
		return (127);
	}
	paths = get_paths_cmds(env_path);
	free(env_path);
	i = -1;
	exec_command = NULL;
	while (paths[++i])
	{
		builtins->i = i;
		if (set_exec_cmds(&exec_command, arg, paths, builtins) == 0)
			return (0);
	}
	builtins->i = i - 1;
	return (get_status(&exec_command, arg, paths, builtins));
}
