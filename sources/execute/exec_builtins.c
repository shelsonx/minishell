/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjhony-x <sjhony-x@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:50:42 by sjhony-x          #+#    #+#             */
/*   Updated: 2023/03/07 16:50:44 by sjhony-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_export(t_data *data)
{
	if (data->parser_data->index == 1)
		ft_export(data->builtin_vars, data->pipeline);
	else
	{
		if (create_child_process() == 0)
		{
			ft_export(data->builtin_vars, data->pipeline);
			free_children_main(data, NULL);
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}

int	exec_env(t_data *data)
{
	if (data->parser_data->index == 1)
		ft_env(data->builtin_vars);
	else
	{
		if (create_child_process() == 0)
		{
			ft_env(data->builtin_vars);
			free_children_main(data, NULL);
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}

int	exec_cd(t_data *data)
{
	if (data->parser_data->index == 1)
		ft_cd(data);
	else
	{
		if (create_child_process() == 0)
		{
			ft_cd(data);
			free_children_main(data, NULL);
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}

int	exec_pwd(t_data *data)
{
	(void) data;
	if (data->parser_data->index == 1)
		ft_pwd();
	else
	{
		if (create_child_process() == 0)
		{
			ft_pwd();
			free_children_main(data, NULL);
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}

int	exec_unset(t_data *data)
{
	if (data->parser_data->index == 1)
		ft_unset(data->builtin_vars, data->pipeline);
	else
	{
		if (create_child_process() == 0)
		{
			ft_unset(data->builtin_vars, data->pipeline);
			free_children_main(data, NULL);
			exit(EXIT_SUCCESS);
		}
	}
	return (0);
}
