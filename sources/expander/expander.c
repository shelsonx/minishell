#include "../../includes/minishell.h"

static void	parameter_expander(char **str, char *parameters, t_builtin_vars *builtin_vars)
{
	int		i;
	char	**splitted;
	char	*env;
	char	*replaced;
	char	*joinned;

	splitted = ft_split(parameters, ' ');
	i = -1;
	while (splitted[++i])
	{
		env = get_env_path(splitted[i], builtin_vars);
		joinned = ft_strjoin("$", splitted[i]);
		replaced = ft_replace_str(*str, joinned, env);
		free(*str);
		free(env);
		*str = replaced;
		free(joinned);
	}
	ft_free_tab(splitted);
}

static char	*get_parameter(char **args, int *x, int *y)
{
	int start;
	char	*parameter;
	char	*sub;

	parameter = ft_strdup("");
	sub = NULL;
	start = -1;
	if (ft_isalpha(args[(*x)][(*y)]) || args[(*x)][(*y)] == '_')
	{
		start = (*y);
		(*y)++;
		if (ft_isalnum(args[(*x)][(*y)]) || args[(*x)][(*y)] == '_')
		{
			while (ft_isalnum(args[(*x)][(*y)]) || args[(*x)][(*y)] == '_')
				(*y)++;
		}
		sub = ft_substr(args[(*x)], start, (*y)-start);
		if (sub)
			parameter = ft_concat_strs(parameter, sub, " ");
	}
	return (parameter);
}

static char	*get_parameters(char **args, int *x, int *y)
{
	char	*parameters;

	parameters = ft_strdup("");
	while (args[(*x)][(*y)])
	{
		if (args[(*x)][(*y)] == '$')
		{
			(*y)++;
			parameters = ft_concat_strs(parameters, get_parameter(args, x, y), " ");
			(*y)--;
		}
		(*y)++;
	}
	return (parameters);
}

static void	expander_special_parameter(char **args, t_data *data)
{
	int		x;
	int		y;
	char	*str_exit_status;
	char	*old_pipeline;

	x = 0;
	while (args[x])
	{
		y = 0;
		while (args[x][y])
		{
			if (args[x][y] == '$' && args[x][y+1] == '?')
			{
				str_exit_status = ft_itoa(*data->exit_status);
				old_pipeline = args[x];
				args[x] = ft_replace_str(args[x], "$?", str_exit_status);
				free(str_exit_status);
				free(old_pipeline);
			}
			y++;
		}
		x++;
	}
}

void    expander(char **args, t_builtin_vars *builtin_vars, t_data *data)
{
	int		x;
	int		y;
	char	*parameters;

	expander_special_parameter(args, data);
	x = 0;
	while (args[x])
	{
		y = 0;
		parameters = get_parameters(args, &x, &y);
		if (args[x][0] != '\'')
			parameter_expander(&args[x], parameters, builtin_vars);
		free(parameters);
		x++;
	}
}
