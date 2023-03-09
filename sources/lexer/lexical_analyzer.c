/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:00:42 by progerio          #+#    #+#             */
/*   Updated: 2023/03/07 17:00:44 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_tokenizer(t_tokenizer *tokenizer)
{
	tokenizer->pos = 0;
	tokenizer->current_char = tokenizer->content[tokenizer->pos];
	tokenizer->characters = ft_strdup("");
	tokenizer->token.value = NULL;
	tokenizer->token.type = -1;
}

t_token	get_next_token(t_tokenizer *tokenizer)
{
	if (tokenizer->token.type != TK_PARENTHESIS)
	{
		tokenizer->token.value = ft_calloc(ft_strlen(
					tokenizer->characters) + 1, sizeof(char));
		ft_strcpy(tokenizer->token.value, tokenizer->characters);
	}
	advance(tokenizer);
	return (tokenizer->token);
}

t_token	next_token(t_tokenizer *tokenizer)
{
	while (tokenizer->token.type != TK_EOF)
	{
		if (ft_isspace(tokenizer->current_char))
			skip_space(tokenizer);
		if (ft_isparenthesis(tokenizer->current_char))
			return (get_parenthesis(tokenizer));
		if (ft_isgreat(tokenizer->current_char))
			return (get_great(tokenizer));
		if (ft_isless(tokenizer->current_char))
			return (get_less(tokenizer));
		if (ft_ispipe(tokenizer->current_char))
			return (get_pipe(tokenizer));
		if (tokenizer->current_char != '\0')
			return (get_word(tokenizer));
		advance(tokenizer);
	}
	return (tokenizer->token);
}
