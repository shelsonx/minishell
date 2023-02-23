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

// NOTE: liberar a memória de todo o programa e os fds
void	interrupt_here_doc(int signal)
{
	int	*fd;

	(void) signal;
	fd = *get_fd_close();
	close(fd[STDIN_FILENO]);
	close(fd[STDOUT_FILENO]);
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
	signal(SIGINT, interrupt_here_doc); //insert
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
