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

static char	ft_isunderscore(char c)
{
	if (c == '_')
		return (true);
	else
		return (false);
}

int	is_valid_id(char *args)
{
	int		i;
	t_data	*data;
	char	*tmp;
	char	*tmp2;

	data = *get_data();
	if (!ft_isunderscore(args[0]) && !ft_isalpha(args[0]))
	{
		tmp = ft_strjoin("minishell: export: ", args);
		tmp2 = ft_strjoin(tmp, ": not a valid identifier");
		ft_putendl_fd(tmp2, 2);
		free(tmp);
		free(tmp2);
		*data->exit_status = 1;
		return (FALSE);
	}
	else
	{
		i = 0;
		while (args[i])
		{
			if (!ft_isunderscore(args[i]) && !ft_isalnum(args[i]))
			{
				tmp = ft_strjoin("minishell: export: ", args);
				tmp2 = ft_strjoin(tmp, ": not a valid identifier");
				ft_putendl_fd(tmp2, 2);
				free(tmp);
				free(tmp2);
				*data->exit_status = 1;
				return (FALSE);
			}
			i++;
		}
	}
	return (TRUE);
}

static void	set_tmp(t_node *current, char **tmp1, char **tmp2, char *args)
{
	if (contains_equal(current->value))
	{
		free(*tmp1);
		*tmp1 = ft_substr(current->value, 0, ft_strlen(current->value) - 1);
	}
	if (contains_equal(args))
	{
		free(*tmp2);
		*tmp2 = ft_substr(args, 0, ft_strlen(args) - 1);
		if (ft_strncmp(current->value, args,
				ft_strlen(current->value)) == 0)
		{
			free(current->value);
			current->value = ft_calloc(ft_strlen(args) + 1, sizeof(char));
			ft_strcpy(current->value, args);
		}
	}
}

int	env_exists(t_builtin_vars *builtins, char *args)
{
	t_node	*current;
	char	*tmp1;
	char	*tmp2;

	current = builtins->env2;
	while (current)
	{
		tmp1 = ft_strdup(current->value);
		tmp2 = ft_strdup(args);
		set_tmp(current, &tmp1, &tmp2, args);
		if (ft_strcmp(tmp1, tmp2) == 0)
		{
			free(tmp1);
			free(tmp2);
			return (TRUE);
		}
		current = current->next;
		free(tmp1);
		free(tmp2);
	}
	return (FALSE);
}
