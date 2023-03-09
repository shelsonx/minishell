/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat_strs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjhony-x <sjhony-x@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:04:41 by sjhony-x          #+#    #+#             */
/*   Updated: 2023/03/07 17:04:42 by sjhony-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_concat_strs(char *str1, char *str2, char *separator)
{
	char	*joinned;
	char	*tmp;

	tmp = ft_strjoin(str1, separator);
	joinned = ft_strjoin(tmp, str2);
	free(tmp);
	free(str1);
	free(str2);
	return (joinned);
}
