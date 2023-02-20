#include "../../includes/minishell.h"

static char **create_new_args(char **args, int *amount)
{
    char    **new_args;
    int     i;
    int     y;
    int     count;

    i = -1;
    count = 0;
    while (args[++i])
        if (ft_strlen(args[i]) > 0)
            count++;
    new_args = ft_calloc(count + 1, sizeof(char *));
    i = -1;
    y = 0;
    while (args[++i])
    {
        if (ft_strlen(args[i]) > 0)
        {
            new_args[y] = ft_calloc(ft_strlen(args[i]) + 1, sizeof(char));
            ft_strcpy(new_args[y], args[i]);
            y++;
        }
    }
    *amount = count;
    return (new_args);
}

static void set_new_values_args(char **args, char **new_args, int amount)
{
    int i;

    i = -1;
    while (new_args[++i])
    {
        free(args[i]);
        args[i] = NULL;
        args[i] = ft_strdup(new_args[i]);
        free(new_args[i]);
    }
    i = amount;
    int total = ft_len_rows_tab(args);
    while (++i <= total)
    {
        free(args[i]);
        args[i] = NULL;
    }
    free(new_args);
    free(args[amount]);
    args[amount] = NULL;
}

static void remove_remmaining_quotes(char **args, char *quote, int x)
{
    char    *old;

    if (ft_strlen(args[x]) > 0)
    {
        while (args[x][ft_strlen(args[x]) -1] == quote[0] && is_quote(quote[0]))
        {
            old = args[x];
            args[x] = ft_strtrim(args[x], quote);
            free(old);
        }
    }
}

void	remove_quotes(char **args)
{
    int     x;
    int     amount;
    char    quote[2];
    char    *old;
    char    **new_args;

    x = 0;
    ft_memset(quote, 0, 2);
    while (args[x])
    {
        if (is_quote(args[x][0]) && is_quote(args[x][ft_strlen(args[x]) -1]))
        {
            quote[0] = args[x][0];
            old = args[x];
            args[x] = ft_strtrim(args[x], quote);
            free(old);
        }
        remove_remmaining_quotes(args, quote, x);
        x++;
    }
    new_args = create_new_args(args, &amount);
    set_new_values_args(args, new_args, amount);
}
