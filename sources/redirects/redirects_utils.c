#include "../../includes/minishell.h"

int has_redirect(t_parser *parser_data, char *redirect, char *index_cmd)
{
    char	*search;
    char	**redirection;
	char	*num_str;
	int		i;

    //expander(redirection, parser_data->builtin_vars);
	i = -1;
	while (++i < parser_data->index_redirect)
	{
		num_str = ft_itoa(i);
		search = ht_search(parser_data->table_redirection, num_str);
    	redirection = ft_split(search, ' ');
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
