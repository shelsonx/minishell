#include "../../includes/minishell.h"

char    *get_comparator(char *arg, int index)
{
    char    **splitted;
    char    *result;

    if (contains_equal(arg))
    {
        splitted = ft_split(arg, '=');
        result = ft_calloc(ft_strlen(splitted[index]) + 2, sizeof(char));
        strcpy(result, splitted[index]);
        ft_free_tab(splitted);
        return (result);
    }
    result = ft_calloc(ft_strlen(arg) + 2, sizeof(char));
    strcpy(result, arg);
    return (result);
}

void ft_free_nodes_env(t_node **lst)
{
	t_node	*next;

	if (!lst)
		return ;
	next = *lst;
	while (next)
	{
		next = next->next;
        if ((*lst)->value)
            free((*lst)->value);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
}

t_node	*ft_new_env(int index, char	*value)
{
	t_node	*node;

	node = (t_node *) malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->index = index;
    node->value = (char*) ft_calloc(ft_strlen(value) + 1, sizeof(char));
	ft_strcpy(node->value, value);
	node->next = NULL;
	return (node);
}
