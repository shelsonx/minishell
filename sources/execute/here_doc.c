#include "../../includes/minishell.h"

static int	is_limiter(char *line, char *limiter)
{
	return (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
		&& (ft_strlen(line)) == ft_strlen(limiter));
}

void	here_doc(int **fd, char *limiter)
{
	char	*line;
	char	*tmp;

	while (TRUE)
	{
		line = readline("> ");
		if (is_limiter(line, limiter))
		{
			free(line);
			close(fd[0][1]);
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		write(fd[0][1], tmp, ft_strlen(tmp));
		free(tmp);
		free(line);
	}
}
