/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjhony-x <sjhony-x@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:59:31 by sjhony-x          #+#    #+#             */
/*   Updated: 2023/03/07 16:59:32 by sjhony-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_fd_out(char **redirection, int *fd_out)
{
	char	*tmp;

	if (strcmp(redirection[0], ">") == 0)
	{
		*fd_out = open(redirection[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (*fd_out < 0)
		{
			*fd_out = INVALID_FD;
			tmp = ft_strjoin("minishell: ", redirection[1]);
			perror(tmp);
			free(tmp);
		}
	}
	if (strcmp(redirection[0], ">>") == 0)
	{
		*fd_out = open(redirection[1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (*fd_out < 0)
		{
			*fd_out = INVALID_FD;
			tmp = ft_strjoin("minishell: ", redirection[1]);
			perror(tmp);
			free(tmp);
		}
	}
}

static void	remove_extra_quotes(char **redirection)
{
	char	*replace;

	replace = ft_replace_str(redirection[1], "\"", "");
	free(redirection[1]);
	redirection[1] = ft_strdup(replace);
	free(replace);
}

static void	free_fd_out(
		t_parser *parser_data, char **num_str, char **redirection)
{
	free(*num_str);
	ft_free_tab(redirection);
	*parser_data->data->exit_status = 1;
}

static int	get(t_parser *parser_data, char *index_cmd, int *file_fd, int i)
{
	char	**redirection;
	char	*search;
	char	*num_str;

	num_str = ft_itoa(i);
	search = ht_search(parser_data->table_redirection, num_str);
	redirection = ft_split(search, 127);
	expander(redirection, parser_data->builtin_vars, parser_data->data);
	remove_quotes(redirection);
	remove_extra_quotes(redirection);
	if (ft_strcmp(redirection[2], index_cmd) == 0)
		set_fd_out(redirection, file_fd);
	if ((has_redirect(parser_data, "<", num_str)
			&& parser_data->index_redirect >= 3) || (*file_fd == INVALID_FD))
	{
		free_fd_out(parser_data, &num_str, redirection);
		return (FALSE);
	}
	free(num_str);
	ft_free_tab(redirection);
	return (TRUE);
}

int	get_fd_out(t_parser *parser_data, char *index_cmd)
{
	int		file_fd;
	int		i;

	file_fd = -1;
	i = -1;
	while (++i < parser_data->index_redirect)
	{
		if (!get(parser_data, index_cmd, &file_fd, i))
		{
			if (file_fd == INVALID_FD)
				return (INVALID_FD);
			else
				return (-1);
		}
	}
	return (file_fd);
}
