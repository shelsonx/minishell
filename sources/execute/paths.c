#include "../../includes/minishell.h"

char **create_args(char **pipeline, t_builtin_vars *builtins)
{
    char	*old_pos;

    old_pos = pipeline[0];
    pipeline[0] = get_exec_command(pipeline[0], builtins);
    free(old_pos);
	return (pipeline);
}

char	**get_paths_cmds(char *env_path)
{
	char	*sub_path;
	char	**paths;

	sub_path = ft_substr(env_path, 5, ft_strlen(env_path));
	paths = ft_split(sub_path, ':');
	free(sub_path);
	return (paths);
}

char	*join_path_command(char *path, char *command)
{
	char	*full_path;
	char	*path_tmp;

	path_tmp = ft_strjoin(path, "/");
	full_path = ft_strjoin(path_tmp, command);
	free(path_tmp);
	return (full_path);
}

int	is_full_path(char *arg, t_builtin_vars *builtins)
{
	int		i;
	char	**paths;
	char	*env_path;
	
	env_path = get_env_path("PATH", builtins);
	paths = get_paths_cmds(env_path);
	i = 0;
	while (paths[i])
	{
		if (ft_strncmp(paths[i], arg, ft_strlen(paths[i])) == 0)
		{
			ft_free_tab(paths);
			free(env_path);
			return (true);
		}
		i++;
	}
	free(env_path);
	ft_free_tab(paths);
	return (false);
}