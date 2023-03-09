/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:59:50 by progerio          #+#    #+#             */
/*   Updated: 2023/03/07 16:59:51 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(void)
{
	char		*current_path;

	current_path = getcwd(NULL, 0);
	if (!current_path)
	{
		printf("error");
	}
	else
	{
		ft_putstr_fd(current_path, 1);
		free(current_path);
	}
	ft_putstr_fd("\n", 1);
}
