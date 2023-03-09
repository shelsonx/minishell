/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_in.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjhony-x <sjhony-x@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:59:27 by sjhony-x          #+#    #+#             */
/*   Updated: 2023/03/07 16:59:28 by sjhony-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_fd_in(char **redirection, int *fd)
{
	char	*tmp;

	*fd = open(redirection[1], O_RDONLY);
	if (*fd < 0)
	{
		*fd = INVALID_FD;
		tmp = ft_strjoin("minishell: ", redirection[1]);
		perror(tmp);
		free(tmp);
	}
}

static void	set_here_doc(char **redirection, int *fd_in, t_parser *parser_data)
{
	int		fd[2];
	int		wstatus;
	pid_t	pid;

	if (pipe(fd) < 0)
	{
		perror("minishell: ");
		return ;
	}
	pid = fork();
	if (pid == FORKED)
		heredoc_children(parser_data, fd, redirection);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &wstatus, 0);
	signal(SIGINT, sighandler);
	close(fd[STDOUT_FILENO]);
	*fd_in = fd[STDIN_FILENO];
	if (WEXITSTATUS(wstatus))
	{
		*fd_in = INVALID_FD;
		close(fd[STDIN_FILENO]);
	}
}

static void	set_fds_in(t_parser *parser_data,
			int *fd_in, char *index_cmd, int i)
{
	char	*search;
	char	**redirection;
	char	*num_str;

	num_str = ft_itoa(i);
	search = ht_search(parser_data->table_redirection, num_str);
	redirection = ft_split(search, 127);
	expander(redirection, parser_data->builtin_vars, parser_data->data);
	remove_quotes(redirection);
	if (ft_strcmp(redirection[2], index_cmd) == 0)
	{
		if (strcmp(redirection[0], "<") == 0)
			set_fd_in(redirection, fd_in);
		if (strcmp(redirection[0], "<<") == 0)
		{
			free(num_str);
			num_str = NULL;
			parser_data->builtin_vars->redirection = redirection;
			set_here_doc(redirection, fd_in, parser_data);
		}
	}
	ft_free_tab(redirection);
	free(num_str);
}

int	get_fd_in(t_parser *parser_data, char *index_cmd)
{
	int	i;
	int	fd_in;

	fd_in = -1;
	i = -1;
	while (++i < parser_data->index_redirect)
	{
		if (fd_in == INVALID_FD)
		{
			*parser_data->data->exit_status = 1;
			break ;
		}
		set_fds_in(parser_data, &fd_in, index_cmd, i);
	}
	return (fd_in);
}
