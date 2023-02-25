#include "../../includes/minishell.h"

char	*get_exec_command(char *arg, t_builtin_vars *builtins)
{
	char	*exec_command;
	char	**paths;

	paths = get_paths(builtins);
	builtins->i = -1;
	while (paths[++builtins->i])
	{
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
