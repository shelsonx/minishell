/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:59:11 by progerio          #+#    #+#             */
/*   Updated: 2023/03/08 16:45:25 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_msg(char *declar, int status)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (status == 2)
	{
		ft_putstr_fd(declar, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	else
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (-1);
	}
	return (0);
}

void	part_of_check_exit(char **declar, int *status_exit, int declar_len)
{
	t_data	*data;

	data = *get_data();
	if (ft_strcmp(declar[1], "-9223372036854775809") == 0)
	{
		ft_free_tab(declar);
		free_ft_exit(data);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (*(declar + 1) && check_str_nb(*(declar + 1)) == 0)
		*status_exit = error_msg(*(declar + 1), 2);
	else if (declar_len > 2)
		*status_exit = error_msg("", 1);
	if (*status_exit > 0 && *status_exit)
	{
		ft_free_tab(declar);
		free_ft_exit(data);
		exit(*status_exit);
	}
}

static void	check_exit(char **declar, int declar_len)
{
	float	value;
	int		status_exit;

	status_exit = 0;
	part_of_check_exit(declar, &status_exit, declar_len);
	value = ft_atoi(*(declar + 1));
	trated_exits(declar, status_exit, &value);
	if (status_exit == -1)
		return ;
	exit((unsigned char)value);
}

void	ft_exit(char **declar)
{
	int		declar_len;
	t_data	*data;

	data = *get_data();
	declar_len = check_len(declar);
	if (declar_len == 1)
	{
		ft_free_tab(declar);
		free_ft_exit(data);
		exit(0);
	}
	else
		check_exit(declar, declar_len);
}
