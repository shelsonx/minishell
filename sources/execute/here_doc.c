#include "../../includes/minishell.h"

static int	is_limiter(char *line, char *limiter)
{
	return (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
		&& (ft_strlen(line)) == ft_strlen(limiter));
}

static void	free_signal_here_doc(void)
{
	t_data	*data;

	data = *get_data();
	free(data->parser_data->tokenizer->characteres);
	free_hashtable(data->parser_data->table_redirection);
	ft_free_nodes_env(&data->builtin_vars->env2);
	ft_free_nodes_env(&data->parser_data->commands);
	ft_free_tab(data->pipeline);
	free(data->parser_data->prompt->line);
	free(data->parser_data->prompt->prompt_str);
	free(data->parser_data->prompt->pwd);
	free(data->parser_data->tokenizer->content);
	free(data->parser_data->current_token);
	free(data->parser_data->tokenizer);
	ft_free_tab(data->parser_data->builtin_vars->redirection);
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
	free_signal_here_doc();
	exit(EXIT_FAILURE);
}

void	message_here_doc(char *line, char *limiter)
{
	printf("minishell: warning: here-document delimited ");
	printf("by end-of-file (wanted `%s')\n", limiter);
	free(line);
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
			message_here_doc(line, limiter);
			break ;
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
