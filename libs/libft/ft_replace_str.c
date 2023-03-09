/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjhony-x <sjhony-x@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:04:20 by sjhony-x          #+#    #+#             */
/*   Updated: 2023/03/07 17:04:22 by sjhony-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_occurrences(const char *s, const char *old)
{
	int		i;
	int		count;
	int		old_len;

	i = 0;
	count = 0;
	old_len = ft_strlen(old);
	while (s[i])
	{
		if (ft_strnstr(&s[i], old, ft_strlen(s)) == &s[i])
		{
			count++;
			i += old_len - 1;
		}
		i++;
	}
	return (count);
}

char	*ft_replace_str(const char *s, const char *old, const char *new)
{
	char	*result;
	int		i;
	int		new_len;
	int		old_len;

	new_len = ft_strlen(new);
	old_len = ft_strlen(old);
	result = malloc(ft_strlen(s)
			+ count_occurrences(s, old) * (new_len - old_len) + 1);
	i = 0;
	while (*s)
	{
		if (ft_strnstr(s, old, ft_strlen(s)) == s)
		{
			ft_strcpy(&result[i], (char *) new);
			i += new_len;
			s += old_len;
		}
		else
			result[i++] = *s++;
	}
	result[i] = '\0';
	return (result);
}
