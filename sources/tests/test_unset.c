#include "../../includes/minishell.h"

// cc test_unset.c test_export.c ../builtins/env.c ../utils/ht_functions.c ../utils/ht_utils.c ../utils/linkedlist_utils.c ../../libs/libft/libft.a

int is_equal_values(t_builtin_vars *builtins, char *args);
int get_position_env(t_builtin_vars *builtins, char *args);
void delete_args_in_ht(t_builtin_vars *builtins, char *key);
int check_if_is_equal(char *args);
void insert_args_in_ht(t_builtin_vars *builtins, char *key, char *value);
void print_export(t_builtin_vars *builtins);

void ft_unset(t_builtin_vars *builtins, char **args)
{
    int i = 1;

    while(args[i])
    {
        if (is_equal_values(builtins, args[i]))
        {
            int position = get_position_env(builtins, args[i]);
            delete_args_in_ht(builtins, ft_itoa(position));
            insert_args_in_ht(builtins, ft_itoa(position), ft_strdup(""));
            return;
        }
        i++;
    }
}

int main(int argc, char **argv, char **envp)
{
	t_builtin_vars builtins;
    init_env(&builtins, envp);

    ft_unset(&builtins, argv);
   

    print_export(&builtins);
}