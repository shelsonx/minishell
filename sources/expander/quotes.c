#include "../../includes/minishell.h"

void	remove_quotes(char **args)
{
    int     x;
    char    quote[2];
    char    *old;

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
        x++;
    }

    //calculate amount values
	int count = 0;
    int i = -1;
    while (args[++i])
        if (ft_strlen(args[i]) > 0)
            count++;
    
    //create new_args to save news values
    char    **new_args = ft_calloc(count + 1, sizeof(char *));
    i = -1;
    int y = 0;
    while (args[++i])
    {
        if (ft_strlen(args[i]) > 0)
        {
            new_args[y] = ft_calloc(ft_strlen(args[i]) + 1, sizeof(char));
            ft_strcpy(new_args[y], args[i]);
            y++;
        }
    }

    //empty args and copy values of the new_args to args    
    i = -1;
    while (new_args[++i])
    {
        free(args[i]);
        args[i] = NULL;
        args[i] = ft_strdup(new_args[i]);
        free(new_args[i]);
    }
    //clear remaining
    i = count;
    int total = ft_len_rows_tab(args);
    while (++i <= total)
    {
        free(args[i]);
        args[i] = NULL;
    }
    free(new_args);
    free(args[count]);
    args[count] = NULL;
}
