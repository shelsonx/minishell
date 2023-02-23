#include "../../includes/minishell.h"

# define FORKED 0

static void	set_fd_in(char **redirection, int *fd)
{
	char	*tmp;

	*fd = open(redirection[1], O_RDONLY);
	if (*fd < 0)
	{
		tmp = ft_strjoin("minishell: ", redirection[1]);
		perror(tmp);
		free(tmp);
	}
}

// alterando aqui
static void	set_here_doc(char **redirection, int *fd_in)
{
	int	fd[2];
	int	wstatus;

	if (pipe(fd) < 0)
	{
		perror("minishell: ");
		return ;
	}
	if (fork() == FORKED)
	{
		here_doc(fd, redirection[1]);
		close(fd[STDIN_FILENO]);
		close(fd[STDOUT_FILENO]);
		exit(EXIT_SUCCESS);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(-1, &wstatus, 0);
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
	redirection = ft_split(search, ' ');
	expander(redirection, parser_data->builtin_vars, parser_data->data);
	if (ft_strcmp(redirection[2], index_cmd) == 0)
	{
		if (strcmp(redirection[0], "<") == 0)
			set_fd_in(redirection, fd_in);
		if (strcmp(redirection[0], "<<") == 0)
			set_here_doc(redirection, fd_in);
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
		set_fds_in(parser_data, &fd_in, index_cmd, i);
	return (fd_in);
}
