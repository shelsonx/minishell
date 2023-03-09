/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:59:19 by progerio          #+#    #+#             */
/*   Updated: 2023/03/08 16:48:38 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_export_data(t_update_export *up_export)
{
	free(up_export->tmp1);
	up_export->tmp1 = NULL;
	free(up_export->tmp2);
	up_export->tmp2 = NULL;
	ft_free_tab(up_export->splitted_args);
	ft_free_tab(up_export->splitted_ht_search);
}

static void	set_tmp(t_update_export *up_export)
{
	if (up_export->splitted_args[1] == NULL)
		up_export->tmp1 = ft_strdup("");
	else
		up_export->tmp1 = ft_strdup(up_export->splitted_args[1]);
	if (up_export->splitted_ht_search[1] == NULL)
		up_export->tmp2 = ft_strdup("");
	else
		up_export->tmp2 = ft_strdup(up_export->splitted_ht_search[1]);
}

int	to_update(t_builtin_vars *builtins, char *args)
{
	t_update_export	up;
	t_node			*current;

	up.tmp1 = NULL;
	up.tmp2 = NULL;
	current = builtins->env2;
	while (current)
	{
		up.splitted_args = ft_split(args, '=');
		up.splitted_ht_search = ft_split(current->value, '=');
		up.res1 = ft_strcmp(up.splitted_args[0], up.splitted_ht_search[0]);
		if (up.res1 == 0)
		{
			set_tmp(&up);
			up.res2 = ft_strcmp(up.tmp1, up.tmp2);
			if (up.res2 != 0)
			{
				free_export_data(&up);
				return (TRUE);
			}
		}
		current = current->next;
		free_export_data(&up);
	}
	return (FALSE);
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
	sort_queue(&builtins->env2, ft_size(builtins->env2));
}
