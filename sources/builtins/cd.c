#include "../../includes/minishell.h"


static void change_value(t_node *current, char **splitted, char *value)
{
    char    *tmp;
    char    *tmp2;

    tmp = ft_strjoin(splitted[0], "=");
    tmp2 = ft_strjoin(tmp, value);
    free(current->value);
    current->value = NULL;
    current->value = ft_calloc(ft_strlen(tmp2) + 2, sizeof(char));
    ft_strcpy(current->value, tmp2);
    free(tmp);
    free(tmp2);
}

void    ft_setenv(t_builtin_vars *builtins, char *name, char *value)
{
    char    **splitted;
    t_node  *current;

    current = builtins->env2;
    while (current->next)
    {
        splitted = ft_split(current->value, '=');
        if (ft_strcmp(name, splitted[0]) == 0)
        {
            change_value(current, splitted, value);
            ft_free_tab(splitted);
            return ;
        }
        ft_free_tab(splitted);
        current = current->next;
    }
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
    size_t  size;
    char    *dir_param;
    char    *tmp;
    char    *env_path;

    size = ft_len_rows_tab(data->pipeline);
    if(size > 2)
        return NULL;
    else if (size == 1)
    {
        env_path = get_env_path("HOME", data->builtin_vars);
        return (env_path);
    }
    
    tmp = check_dots(data->pipeline);
    if (tmp)
    {

        dir_param = ft_calloc(ft_strlen(tmp) + 1, sizeof(char));
        ft_strcpy(dir_param, tmp);
    }
    else
        dir_param = tmp;
    if (dir_param == NULL)
    {
        dir_param = ft_calloc(ft_strlen(data->pipeline[1]) + 1, sizeof(char));
        ft_strcpy(dir_param, data->pipeline[1]);
    }
    return dir_param;
}

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
        perror(new_directory);
        free(new_directory);
        return;
    }
    oldpwd = get_env_path("PWD", data->builtin_vars);
    ft_setenv(data->builtin_vars, "OLDPWD", oldpwd); 
    free(oldpwd);
    getcwd(pwd, 1024);
    ft_setenv(data->builtin_vars, "PWD", pwd);
    free(new_directory);
}