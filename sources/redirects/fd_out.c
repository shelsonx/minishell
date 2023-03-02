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

int	get_fd_out(t_parser *parser_data, char *index_cmd)
{
	char	**redirection;
	char	*search;
	char	*num_str;
	int		file_fd;
	int		i;

	file_fd = -1;
	i = -1;
	while (++i < parser_data->index_redirect)
	{
		num_str = ft_itoa(i);
		search = ht_search(parser_data->table_redirection, num_str);
		redirection = ft_split(search, ' ');
		expander(redirection, parser_data->builtin_vars, parser_data->data);
		remove_quotes(redirection);
		/* if (contains_quotes(redirection[1]))
		{
			char *replaced = ft_replace_str(redirection[1], "\"", "");
			free(redirection[1]);
			redirection[1] = ft_strdup(replaced);
			free(replaced);
		} */
		if (ft_strcmp(redirection[2], index_cmd) == 0)
			set_fd_out(redirection, &file_fd);
		if (file_fd == INVALID_FD)
		{
			*parser_data->data->exit_status = 1;
			break ;
		}
		free(num_str);
		ft_free_tab(redirection);
	}
	return (file_fd);
}
