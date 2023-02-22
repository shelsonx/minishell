#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1)
		ft_putendl_fd("Invalid arguments!", 2);
	else
		prompt(envp);
	(void) argv;
	return (0);
}
