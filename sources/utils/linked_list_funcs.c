#include "../../includes/minishell.h"

t_node	*ft_last(t_node *lst)
{
	if (!lst)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_add_back(t_node **lst, t_node *new_node)
{
	t_node	*last;

	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	last = ft_last(*lst);
	last->next = new_node;
}

void	ft_add_front(t_node **lst, t_node *new_node)
{
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	new_node->next = *lst;
	*lst = new_node;
}

int	ft_size(t_node *lst)
{
	int		count;
	t_node	*tmp;

	if (!lst)
		return (0);
	count = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

t_node	*ft_new(int index, char	*value)
{
	t_node	*node;

	node = (t_node *) malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->index = index;
	node->value = value;
	node->next = NULL;
	return (node);
}
