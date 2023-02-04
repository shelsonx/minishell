#include "../../includes/minishell.h"

int is_valid_identifier_2(char *key);
int contains_equal(char *key);
int env_exists(t_builtin_vars *builtins, char *args);

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
            if(contains_equal(current->value))
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
    if (env_exists(builtins, value))
    {
        return ;
    }
	ft_add_back(&builtins->env2, ft_new_env(ft_atoi(key), value));
}

void insert_args_in_export(t_builtin_vars *builtins, char *args)
{
    add_env_path(builtins, "1", args);
}

int update_value(t_builtin_vars *builtins, char *args)
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

int env_exists(t_builtin_vars *builtins, char *args)
{
    t_node  *current;

    current = builtins->env2;
    while(current)
    {
        if(ft_strcmp(current->value, args) == 0)
            return TRUE;
        current = current->next;
    }
    return FALSE;
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
    } 
    else {
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

int contains_equal(char *args)
{

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
    int position;

    while(args[i])
    {
        if (update_value(builtins, args[i]))
        {
            position = get_position(builtins, args[i]);
            del_pos(&builtins->env2, position);
            add_env_path(builtins, "1", args[i]);
        }
        else
        {
            if(!contains_equal(args[i]))
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
