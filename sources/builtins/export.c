#include "../../includes/minishell.h"

int is_valid_identifier_2(char *key);
int check_if_is_equal(char *key);

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
    node->value = ft_calloc(ft_strlen(value) + 1, sizeof(char));
	ft_strcpy(node->value, value);
	node->next = NULL;
	return (node);
}

void print_export(t_builtin_vars *builtins)
{
    char    **splitter_env;
    char    *key;
    char    *value;
    t_node  *current;

    current = builtins->env2;
    while (current)
    {
        splitter_env = ft_split(current->value, '=');
        key = splitter_env[0];
        value = splitter_env[1];

        if (!value)
        {
            if(check_if_is_equal(current->value))
                printf("declare -x %s\"\"\n", current->value);
            else
                printf("declare -x %s\n", current->value);
        }
        else
		    printf("declare -x %s=\"%s\"\n", key, value);
        ft_free_tab(splitter_env);
        current = current->next;
    } 
}

void add_env_path(t_builtin_vars *builtins, char *key, char *value)
{   
	ft_add_back(&builtins->env2, ft_new_env(ft_atoi(key), value));
}

void delete_args_in_ht(t_builtin_vars *builtins, char *key)
{   
	ht_delete(builtins->env, key);
    builtins->size--;
}

void insert_args_in_export(t_builtin_vars *builtins, char *args)
{
    add_env_path(builtins, "1", args);
}

int key_exists(t_builtin_vars *builtins, char *args)
{
    char **splitted_args; 
    char *num_str;
    int i;

    i = 0;
    while(i < builtins->size)
    {   
        num_str = ft_itoa(i);
        
        if(check_if_is_equal(args))
        {
            splitted_args = ft_split(args, '=');

            if(ft_strncmp(args, ht_search(builtins->env, num_str), ft_strlen(splitted_args[0])) == 0)
                return TRUE;

        } else{
            if(ft_strcmp(args, ht_search(builtins->env, num_str)) == 0)
                return TRUE;
        }
        i++;
    }
    return FALSE;
}

int is_equal_values(t_builtin_vars *builtins, char *args)
{
    char    **splitted_args; 
    char    **splitted_ht_search; 
    t_node  *current;

    current = builtins->env2;
    while(current)
    {
        splitted_args = ft_split(args, '=');
        splitted_ht_search = ft_split(current->value, '=');
        if(ft_strcmp(splitted_args[0], splitted_ht_search[0]) == 0 &&  
            ft_strcmp(splitted_args[1], splitted_ht_search[1]) != 0)
            return TRUE;
        current = current->next;
        ft_free_tab(splitted_args);
        ft_free_tab(splitted_ht_search);
    }
    return FALSE;
}

int get_position_env(t_builtin_vars *builtins, char *args)
{   
    char *num_str;
    char *search;
    char    **splitted;
    int i;

    i = 0;
    while(i < builtins->size)
    {
        num_str = ft_itoa(i);
        search = ht_search(builtins->env, num_str);
        if (check_if_is_equal(args))
        {
            splitted = ft_split(args, '=');
            if (ft_strncmp(search, args, ft_strlen(splitted[0])) == 0)
                return (i);
        }
        i++;
    }
    return -1;
}

char	ft_isunderscore(char c)
{
	if (c == '_')
		return (true);
	else
		return (false);
}

int is_valid_identifier_2(char *args)
{
    if (!ft_isunderscore(args[0]) && !ft_isalpha(args[0]))
    {
        printf("minishell: export: `%s': not a valid identifier\n", args);
        return (FALSE);
    } else {
        int i = 0;
        while(args[i])
        {
            if (!ft_isunderscore(args[i]) && !ft_isalnum(args[i]))
            {
              printf("minishell: export: `%s': not a valid identifier\n", args);
              return (FALSE);  
            }
            i++;    
        }
    }
    return (TRUE);
}

int check_if_is_equal(char *args) {
    int i = 0 ;
        while(args[i])
        {
            if(args[i] == '=')
                {
                    return TRUE;
                }
            i++;
        }
        return FALSE;
    }

void    ft_export_aux(t_builtin_vars *builtins, char **args)
{
    int i = 1;
    char **splitter_equals;

    while(args[i])
    {
        if (is_equal_values(builtins, args[i]))
        {
            int position = get_position_env(builtins, args[i]);
            delete_args_in_ht(builtins, ft_itoa(position));
            add_env_path(builtins, ft_itoa(position), args[i]);
        }
        else
        {
            if(!check_if_is_equal(args[i]))
            {
                if(is_valid_identifier_2(args[i]))
                    insert_args_in_export(builtins, args[i]);
            }
            else
            {
                splitter_equals = ft_split(args[i], '=');
                if(ft_strlen(args[i]) > 1)
                {
                    if(is_valid_identifier_2(splitter_equals[0]))
                        insert_args_in_export(builtins, args[i]);
                }
                else
                {
                    if(is_valid_identifier_2(args[i]))
                        insert_args_in_export(builtins, args[i]);
                }
                ft_free_tab(splitter_equals);
            }
        }
        i++; 
    }
}

void    ft_export(t_builtin_vars *builtins, char **args)
{
    if (ft_len_rows_tab(args) == 1)
        print_export(builtins);
    if (ft_len_rows_tab(args) > 1)
        ft_export_aux(builtins, args);
}
