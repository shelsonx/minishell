#include "../../includes/minishell.h"

int	is_valid_identifier_2(char *key);
int	contains_equal(char *key);
int	env_exists(t_builtin_vars *builtins, char *args);

void	print_export(t_builtin_vars *builtins)
{
	char	**splitter_env;
	char	*key;
	char	*value;
	t_node	*current;

	current = builtins->env2;
	while (current)
	{
		splitter_env = ft_split(current->value, '=');
		key = splitter_env[0];
		value = splitter_env[1];
		if (!value)
		{
			if (contains_equal(current->value))
				printf("declare -x %s\"\"\n", current->value);
			else
				printf("declare -x %s\n", current->value);
		}
		else
			printf("declare -x %s=\"%s\"\n", key, value);
		ft_free_tab(splitter_env);
		current = current->next;
	}
}

void	add_env_path(t_builtin_vars *builtins, char *key, char *value)
{
	if (env_exists(builtins, value))
	{
		return ;
	}
	ft_add_back(&builtins->env2, ft_new_env(ft_atoi(key), value));
}

void	insert_args_in_export(t_builtin_vars *builtins, char *args)
{
	add_env_path(builtins, "1", args);
}

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
		if (contains_equal(current->value))
		{
			free(tmp1);
			tmp1 = ft_substr(current->value, 0, ft_strlen(current->value) - 1);
		}
		if (contains_equal(args))
		{
			free(tmp2);
			tmp2 = ft_substr(args, 0, ft_strlen(args) - 1);
			if (ft_strncmp(current->value, args,
					ft_strlen(current->value)) == 0)
			{
				free(current->value);
				current->value = ft_calloc(ft_strlen(args) + 1, sizeof(char));
				ft_strcpy(current->value, args);
			}
		}
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

char	ft_isunderscore(char c)
{
	if (c == '_')
		return (true);
	else
		return (false);
}

int	is_valid_identifier_2(char *args)
{
	int		i;

	if (!ft_isunderscore(args[0]) && !ft_isalpha(args[0]))
	{
		printf("minishell: export: `%s': not a valid identifier\n", args);
		return (FALSE);
	}
	else
	{
		i = 0;
		while (args[i])
		{
			if (!ft_isunderscore(args[i]) && !ft_isalnum(args[i]))
			{
				printf("minishell: export: `%s': not a valid identifier\n",
					args);
				return (FALSE);
			}
			i++;
		}
	}
	return (TRUE);
}

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

static void	set_in_export(t_builtin_vars *builtins, char **args, int i)
{
	char	**splitter_equals;

	if (!contains_equal(args[i]))
	{
		if (is_valid_identifier_2(args[i]))
			insert_args_in_export(builtins, args[i]);
	}
	else
	{
		splitter_equals = ft_split(args[i], '=');
		if (ft_strlen(args[i]) > 1)
		{
			if (is_valid_identifier_2(splitter_equals[0]))
				insert_args_in_export(builtins, args[i]);
		}
		else
		{
			if (is_valid_identifier_2(args[i]))
				insert_args_in_export(builtins, args[i]);
		}
		ft_free_tab(splitter_equals);
	}
}

static void update(t_builtin_vars *builtins, char **args, int i)
{
	int	position;

	position = get_position(builtins, args[i]);
	del_pos(&builtins->env2, position);
	add_env_path(builtins, "1", args[i]);
}

void	export(t_builtin_vars *builtins, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (to_update(builtins, args[i]))
			update(builtins, args, i);
		else
			set_in_export(builtins, args, i);
		i++;
	}
}

void	ft_export(t_builtin_vars *builtins, char **args)
{
	if (ft_len_rows_tab(args) == 1)
		print_export(builtins);
	if (ft_len_rows_tab(args) > 1)
		export(builtins, args);
}
