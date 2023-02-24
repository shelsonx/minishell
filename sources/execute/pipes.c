#include "../../includes/minishell.h"

static int	get_amount_parameters(t_parser *parser_data, int index_cmd)
{
	t_node	*current;
	int		amount;

	current = parser_data->commands;
	amount = 0;
	while (current)
	{
		if (current->index == index_cmd)
			amount++;
		current = current->next;
	}
	return (amount);
}

char	**get_pipeline(t_data *data, t_parser *parser_data, int index_cmd)
{
	t_node	*current;
	int		i;

	data->pipeline = ft_calloc(get_amount_parameters(
				parser_data, index_cmd) + 1, sizeof(char *));
	current = parser_data->commands;
	i = 0;
	while (current)
	{
		if (current->index == index_cmd)
		{
			data->pipeline[i] = ft_calloc(ft_strlen(
						current->value) + 1, sizeof(char));
			ft_strcpy(data->pipeline[i], current->value);
			i++;
		}
		current = current->next;
	}
	return (data->pipeline);
}

int	**create_pipes(int amount)
{
	int		i;
	int		**tube;

	tube = ft_calloc
		(sizeof(int **), (amount + 1));
	i = 0;
	while (i < amount)
	{
		tube[i] = ft_calloc(sizeof(int *), 2);
		if (pipe(tube[i]) < 0)
		{
			perror("Error: ");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (tube);
}
