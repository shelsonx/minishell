#include "../../includes/minishell.h"

static int	is_limiter(char *line, char *limiter)
{
	return (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
		&& (ft_strlen(line)) == ft_strlen(limiter));
}

int	**get_fd_close(void)
{
    static int	*fd;

    return (&fd);
}

static void free_sinal_here_doc(void)
{
	extern t_data *ms_data;

	free(ms_data->parser_data->tokenizer->characteres);
	free_hashtable(ms_data->parser_data->table_redirection);
	ft_free_nodes_env(&ms_data->builtin_vars->env2);
	ft_free_nodes_env(&ms_data->parser_data->commands);
	ft_free_tab(ms_data->pipeline);
	free(ms_data->parser_data->prompt->line);
	free(ms_data->parser_data->prompt->prompt_str);
	free(ms_data->parser_data->prompt->pwd);
	free(ms_data->parser_data->tokenizer->content);
	free(ms_data->parser_data->current_token);
	free(ms_data->parser_data->tokenizer);
	ft_free_tab(ms_data->parser_data->builtin_vars->redirection);
	rl_clear_history();
}

void	interrupt_here_doc(int signal)
{
	int	*fd;

	(void) signal;
	printf("\n");
	fd = *get_fd_close();
	close(fd[STDIN_FILENO]);
	close(fd[STDOUT_FILENO]);
	free_sinal_here_doc();
	exit(EXIT_FAILURE);
}

void	set_fd_close(int *fd)
{
    int	**save;

    save = get_fd_close();
    *save = fd;
}

void	here_doc(int fd[], char *limiter)
{
	char	*line;
	char	*tmp;

	set_fd_close(fd);
	signal(SIGINT, interrupt_here_doc);
	signal(SIGQUIT, SIG_IGN);
	while (TRUE)
	{
		line = readline("> ");
		if (line == NULL)
		{
			free(line);
			break;
		}
		if (is_limiter(line, limiter))
		{
			free(line);
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		write(fd[1], tmp, ft_strlen(tmp));
		free(tmp);
		free(line);
	}
}
