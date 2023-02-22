#include "../../includes/minishell.h"

void	ft_pwd(void)
{
	char		*current_path;

	current_path = getcwd(NULL, 0);
	if (!current_path)
	{
		printf("error");
	}
	else
	{
		ft_putstr_fd(current_path, 1);
		free(current_path);
	}
	ft_putstr_fd("\n", 1);
}
