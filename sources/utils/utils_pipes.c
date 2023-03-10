/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:02:35 by progerio          #+#    #+#             */
/*   Updated: 2023/03/07 17:02:37 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_fds(int **fds)
{
	int	i;

	i = 0;
	if (!fds)
		return ;
	while (fds[i])
	{
		if (fds[i])
		{
			free(fds[i]);
			fds[i] = NULL;
		}
		i++;
	}
	free(fds);
}

void	ft_close_fds(int **fds)
{
	int	i;

	if (!fds)
		return ;
	i = 0;
	while (fds[i])
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
}
