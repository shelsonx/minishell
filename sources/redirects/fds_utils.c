/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjhony-x <sjhony-x@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:59:36 by sjhony-x          #+#    #+#             */
/*   Updated: 2023/03/07 16:59:37 by sjhony-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_in(t_parser *parser_data, char *index_cmd, int *fd_in)
{
	*fd_in = get_fd_in(parser_data, index_cmd);
	if (*fd_in == INVALID_FD)
	{
		*parser_data->data->exit_status = 1;
		return (FALSE);
	}
	return (TRUE);
}

int	set_out(t_parser *parser_data, char *index_cmd, int *fd_out)
{
	*fd_out = get_fd_out(parser_data, index_cmd);
	if (*fd_out == INVALID_FD)
	{
		*parser_data->data->exit_status = 1;
		return (FALSE);
	}
	return (TRUE);
}

int	set_fds(t_parser *parser_data, char *index_cmd, int *fd_in, int *fd_out)
{
	char	*search;
	char	**redirection;

	search = ht_search(parser_data->table_redirection, index_cmd);
	if (search)
	{
		redirection = ft_split(search, 127);
		if (ft_strcmp(redirection[0], "<") == 0
			|| ft_strcmp(redirection[0], "<<") == 0)
		{
			if (!set_in(parser_data, index_cmd, fd_in))
				return (FALSE);
			if (!set_out(parser_data, index_cmd, fd_out))
				return (FALSE);
		}
		else
		{
			if (!set_out(parser_data, index_cmd, fd_out))
				return (FALSE);
			if (!set_in(parser_data, index_cmd, fd_in))
				return (FALSE);
		}
	}
	return (TRUE);
}
