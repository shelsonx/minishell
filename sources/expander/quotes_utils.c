#include "../../includes/minishell.h"

int	contains_quotes(char *arg)
{
	int		i;

	i = -1;
	while (arg[++i])
		if (arg[i] == '\'' || arg[i] == '\"')
			return (TRUE);
	return (FALSE);
}

void	remove_sides(char quote[], char **args, int x)
{
	char	*old;

	quote[0] = args[x][0];
	old = args[x];
	args[x] = ft_strtrim(args[x], quote);
	free(old);
}
