#include "../../includes/minishell.h"

static void set_fd_out(char **redirection, int *fd_out)
{
    if (strcmp(redirection[0], ">") == 0)
    {
        *fd_out = open(redirection[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (*fd_out < 0)
            perror("minishell");
    }
    if (strcmp(redirection[0], ">>") == 0)
    {
        *fd_out = open(redirection[1], O_WRONLY | O_CREAT | O_APPEND, 0777);
        if (*fd_out < 0)
            perror("minishell");
    }
}

int	get_fd_out(t_parser *parser_data, char *index_cmd)
{
	char	**redirection;
	char	*search;
	int 	file_fd;
	int		i;

	file_fd = -1;
	i = -1;
	while (++i < parser_data->index_redirect)
	{
		search = ht_search(parser_data->table_redirection, ft_itoa(i));
		redirection = ft_split(search, ' ');
		//expander(redirection, parser_data->builtin_vars);
		if (ft_strcmp(redirection[2], index_cmd) == 0)
            set_fd_out(redirection, &file_fd);
	}
	return (file_fd);
}
