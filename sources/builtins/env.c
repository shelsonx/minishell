/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:58:58 by progerio          #+#    #+#             */
/*   Updated: 2023/03/07 16:58:59 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_path(char *path, t_builtin_vars *builtin)
{
	char	*env_path;
	t_node	*current;
	char	**splitted;

	current = builtin->env2;
	while (current)
	{
		if (contains_equal(current->value))
		{
			splitted = ft_split(current->value, '=');
			if (ft_strcmp(path, splitted[0]) == 0)
			{	
				if (splitted[1])
					env_path = ft_strdup(splitted[1]);
				else
					env_path = ft_strdup("");
				ft_free_tab(splitted);
				return (env_path);
			}
			ft_free_tab(splitted);
		}
		current = current->next;
	}
	env_path = ft_strdup("");
	return (env_path);
}

void	init_env(t_builtin_vars *builtin_vars, char **envp)
{
	int		i;

	i = -1;
	builtin_vars->env2 = NULL;
	while (envp[++i])
		ft_add_back(&builtin_vars->env2, ft_new_env(i, envp[i]));
	sort_queue(&builtin_vars->env2, ft_size(builtin_vars->env2));
}

void	ft_env(t_builtin_vars *builtin_vars)
{
	t_node	*current;

	current = builtin_vars->env2;
	while (current)
	{
		if (contains_equal(current->value))
			printf("%s\n", current->value);
		current = current->next;
	}
}

char	**get_env(t_builtin_vars *builtin_vars)
{
	char	**env;
	t_node	*current;
	int		i;
	int		size;

	size = ft_size(builtin_vars->env2);
	env = calloc(size + 1, sizeof (char *));
	current = builtin_vars->env2;
	i = -1;
	while (++i < size)
	{
		if (ft_strlen(current->value) > 0)
		{
			env[i] = ft_calloc(ft_strlen(current->value) + 1, sizeof(char));
			ft_strcpy(env[i], current->value);
		}
		current = current->next;
	}
	return (env);
}
