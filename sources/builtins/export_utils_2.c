#include "../../includes/minishell.h"

int	to_update(t_builtin_vars *builtins, char *args)
{
	char	**splitted_args;
	char	**splitted_ht_search;
	char	*tmp1;
	char	*tmp2;
	int		res1;
	int		res2;
	t_node	*current;

	tmp1 = NULL;
	tmp2 = NULL;
	current = builtins->env2;
	while (current)
	{
		splitted_args = ft_split(args, '=');
		splitted_ht_search = ft_split(current->value, '=');
		res1 = ft_strcmp(splitted_args[0], splitted_ht_search[0]);
		if (res1 == 0)
		{
			if (splitted_args[1] == NULL)
				tmp1 = ft_strdup("");
			else
				tmp1 = ft_strdup(splitted_args[1]);
			if (splitted_ht_search[1] == NULL)
				tmp2 = ft_strdup("");
			else
				tmp2 = ft_strdup(splitted_ht_search[1]);
			res2 = ft_strcmp(tmp1, tmp2);
			if (res2 != 0)
			{
				free(tmp1);
				free(tmp2);
				ft_free_tab(splitted_args);
				ft_free_tab(splitted_ht_search);
				return (TRUE);
			}
		}
		current = current->next;
		free(tmp1);
		free(tmp2);
		ft_free_tab(splitted_args);
		ft_free_tab(splitted_ht_search);
	}
	return (FALSE);
}