#include "../../includes/minishell.h"

int	contains_equal(char *args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '=')
		{
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

char	ft_isunderscore(char c)
{
	if (c == '_')
		return (true);
	else
		return (false);
}
