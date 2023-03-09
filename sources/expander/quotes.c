/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:01:44 by sjhony-x          #+#    #+#             */
/*   Updated: 2023/03/08 16:48:11 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_between_chars(char **arg)
{
	char	*replaced;
	char	quote[2];
	char	*tmp;

	replaced = NULL;
	ft_memset(quote, 0, 2);
	if (contains_quotes(*arg))
	{
		tmp = ft_strchr(*arg, '\'');
		if (tmp)
			quote[0] = tmp[0];
		else
		{
			tmp = ft_strchr(*arg, '\"');
			quote[0] = tmp[0];
		}
		replaced = ft_replace_str(*arg, quote, "");
		free(*arg);
		*arg = ft_strdup(replaced);
		free(replaced);
		replaced = NULL;
	}
}

static void	remove_remmaining_quotes(char **args, char *quote, int x)
{
	char	*old;

	if (ft_strlen(args[x]) > 0)
	{
		while (args[x][ft_strlen(args[x]) - 1] == quote[0]
							&& is_quote(quote[0]))
		{
			old = args[x];
			args[x] = ft_strtrim(args[x], quote);
			free(old);
		}
	}
}

static void	set_value_if_is_empty(char **args)
{
	char	*old;

	if (args[0] == NULL)
		args[0] = ft_strdup(" ");
	else if (ft_strcmp(args[0], "") == 0)
	{
		old = args[0];
		args[0] = ft_strdup(" ");
		free(old);
	}
}

void	remove_quotes(char **args)
{
	int		x;
	char	quote[2];
	char	*old;

	x = 0;
	ft_memset(quote, 0, 2);
	while (args[x])
	{
		if (is_quote(args[x][0]) && is_quote(args[x][ft_strlen(args[x]) - 1]))
		{
			if (ft_strlen(args[x]) > 2)
				remove_sides(quote, args, x);
			else
			{
				old = args[x];
				args[x] = ft_strdup("");
				free(old);
			}
		}
		else
			remove_between_chars(&args[x]);
		remove_remmaining_quotes(args, quote, x);
		x++;
	}
	set_value_if_is_empty(args);
}
