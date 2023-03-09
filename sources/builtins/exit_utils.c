/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:59:04 by progerio          #+#    #+#             */
/*   Updated: 2023/03/07 16:59:06 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	check_str_nb(char *declar)
{
	if (*declar == '+' || *declar == '-')
		declar++;
	while (*declar && (*declar >= '0' && *declar <= '9'))
		declar++;
	if (*declar == '\0')
		return (1);
	return (0);
}

int	check_len(char **declar)
{
	char	**len;

	len = declar;
	if (!declar)
		return (0);
	while (*len)
		len++;
	return (len - declar);
}

void	trated_exits(char **declar, int status_exit, float *value)
{
	t_data	*data;

	data = *get_data();
	if (ft_strcmp(declar[1], "-9223372036854775808") == 0)
	{
		ft_free_tab(declar);
		free_ft_exit(data);
		exit(0);
	}
	if (status_exit != -1)
	{
		ft_free_tab(declar);
		free_ft_exit(data);
	}
	if (*value == 0)
	{
		error_msg(*declar, 2);
		*value = 2;
	}
}
