#include "../../includes/minishell.h"

int	get_position(t_builtin_vars *builtins, char *arg)
{
	char	*comp1;
	char	*comp2;
	t_node	*current;
	int		position;

	position = 0;
	current = builtins->env2;
	while (current->next)
	{
		comp1 = get_comparator(arg, 0);
		comp2 = get_comparator(current->value, 0);
		if (ft_strcmp(comp1, comp2) == 0)
		{
			free(comp1);
			free(comp2);
			return (position);
		}
		current = current->next;
		position++;
		free(comp1);
		free(comp2);
	}
	return (position);
}

void	del_pos(t_node **head, int position)
{
	t_node	*current;
	t_node	*previous;

	current = *head;
	previous = *head;
	if (*head == NULL)
		return ;
	else if (position == 0)
	{
		*head = current->next;
		free(current->value);
		free(current);
		current = NULL;
	}
	else
	{
		while (position != 0)
		{
			previous = current;
			current = current->next;
			position--;
		}
		previous->next = current->next;
		free(current->value);
		free(current);
		current = NULL;
	}
}

void	ft_unset(t_builtin_vars *builtins, char **args)
{
	int		i;
	int		position;

	i = 0;
	while (args[++i])
	{
		position = get_position(builtins, args[i]);
		if (position >= 0 && position < ft_size(builtins->env2))
			del_pos(&builtins->env2, position);
	}
}
