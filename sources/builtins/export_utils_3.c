/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:59:26 by progerio          #+#    #+#             */
/*   Updated: 2023/03/07 16:59:27 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	ft_isunderscore(char c)
{
	if (c == '_')
		return (true);
	else
		return (false);
}
