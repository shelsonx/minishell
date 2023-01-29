#include "../../includes/minishell.h"

// colocar nossas funções no lugar de getenv e setenv

/* int ft_setenv(t_builtin_vars *builtins, char *args){
    int position = get_position_env(builtins, args);
    if (is_equal_values(builtins, args))
    delete_args_in_ht(builtins, ft_itoa(position));
    insert_args_in_ht(builtins, ft_itoa(position), args);
    return (insert_args_in_ht(builtins, ft_itoa(position), args));
} */

size_t get_size (char **args)
{
    size_t i;

    i = 0;
    while (args[i] != NULL)
        i++;
    return (i);
}

static char *check_dots(char **args)
{
    size_t i;
    char *dir_param;
    static char pwd[1024];

    dir_param = NULL;
    i = ft_strlen(args[1]);
    if(i == 1 && ft_strcmp(".", args[1]) == 0)
    {
        getcwd(pwd, 1024);
        return pwd;
    } 
    else if (i == 2 && ft_strcmp("..", args[1]) == 0)
    {
        dir_param = "..";
    }

    return (dir_param);
}

static char *validate_args(t_data *data)
{
    size_t size;
    char *dir_param;

    size = get_size(data->pipeline);

    if(size > 2)
        return NULL;
    else if (size == 1)
        return get_env_path("HOME", data->builtin_vars); 
    
    dir_param = check_dots(data->pipeline);
    if (dir_param == NULL)
        dir_param = data->pipeline[1];
    return dir_param;
}

// ver como gerenciar erros das builtins em geral
void ft_cd (t_data *data)
{
    char *new_directory;
    char *oldpwd;
    char pwd[1024];

    new_directory = validate_args(data);
    if (new_directory == NULL)
    {
        printf("minishell: cd: too many arguments\n");
        return;
    }
    if (chdir(new_directory))
    {
        perror("minishell: ");
        return;
    }

    oldpwd = get_env_path("PWD", data->builtin_vars);
    
    setenv("OLDPWD", oldpwd, 1); 
    getcwd(pwd, 1024);
    setenv("PWD", pwd, 1);
}