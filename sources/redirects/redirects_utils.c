/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjhony-x <sjhony-x@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:59:44 by sjhony-x          #+#    #+#             */
/*   Updated: 2023/03/07 16:59:46 by sjhony-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_redirect(t_parser *parser_data, char *redirect, char *index_cmd)
{
	char	*search;
	char	**redirection;
	char	*num_str;
	int		i;

	i = -1;
	while (++i < parser_data->index_redirect)
	{
		num_str = ft_itoa(i);
		search = ht_search(parser_data->table_redirection, num_str);
		redirection = ft_split(search, 127);
		expander(redirection, parser_data->builtin_vars, parser_data->data);
		if (ft_strcmp(redirection[2], index_cmd) == 0)
		{
			if (strcmp(redirection[0], redirect) == 0)
			{
				free(num_str);
				ft_free_tab(redirection);
				return (TRUE);
			}
		}
		free(num_str);
		ft_free_tab(redirection);
	}
	return (FALSE);
}

void	set_fds_middle_cmd(t_data *data, t_parser *parser_data, int i)
{
	int		fd_in;
	int		fd_out;
	char	*index_cmd;

	index_cmd = get_input_cmd(i + 1);
	fd_in = get_fd_in(parser_data, index_cmd);
	fd_out = get_fd_out(parser_data, index_cmd);
	if (fd_in == -1)
		data->fd_in = data->fds[i][0];
	else
		data->fd_in = fd_in;
	if (fd_out == -1)
		data->fd_out = data->fds[i + 1][1];
	else
		data->fd_out = fd_out;
}

void	set_fds_first_cmd(t_data *data, int fd_in, int fd_out)
{
	data->fd_in = fd_in;
	if (fd_out == -1)
		data->fd_out = data->fds[0][1];
	else
		data->fd_out = fd_out;
}

int	**get_fd_close(void)
{
	static int	*fd;

	return (&fd);
}

void	set_fd_close(int *fd)
{
	int	**save;

	save = get_fd_close();
	*save = fd;
}
