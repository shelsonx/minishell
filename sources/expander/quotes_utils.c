#include "../../includes/minishell.h"

int	contains_quotes(char *arg)
{
	int		i;

	i = -1;
	while (arg[++i])
		if (arg[i] == '\'' || arg[i] == '\"')
			return (TRUE);
	return (FALSE);
}

void	remove_sides(char quote[], char **args, int x)
{
	char	*old;

	quote[0] = args[x][0];
	old = args[x];
	args[x] = ft_strtrim(args[x], quote);
	free(old);
}

void	set_special_char(t_data *data, char **args, int x)
{
	char	*str_exit_status;
	char	*old_pipeline;

	str_exit_status = ft_itoa(*data->exit_status);
	old_pipeline = args[x];
	args[x] = ft_replace_str(args[x], "$?", str_exit_status);
	free(str_exit_status);
	free(old_pipeline);
}
