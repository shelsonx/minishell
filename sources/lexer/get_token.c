/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:00:32 by progerio          #+#    #+#             */
/*   Updated: 2023/03/08 16:49:37 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	get_word(t_tokenizer *tokenizer)
{
	tk_word(tokenizer);
	if (tokenizer->token.type == TK_ERROR)
		return (tokenizer->token);
	tokenizer->token.value = ft_calloc(
			ft_strlen(tokenizer->characters) + 1, sizeof(char));
	ft_strcpy(tokenizer->token.value, tokenizer->characters);
	if (tokenizer->token.type == TK_ASSIGNMENT_WORD)
		return (tokenizer->token);
	else
		tokenizer->token.type = TK_WORD;
	return (tokenizer->token);
}

t_token	get_parenthesis(t_tokenizer *tokenizer)
{
	add_char(tokenizer);
	tokenizer->token.type = TK_PARENTHESIS;
	return (get_next_token(tokenizer));
}

t_token	get_great(t_tokenizer *tokenizer)
{
	if (ft_isgreat(tokenizer->content[tokenizer->pos +1]))
	{
		tokenizer->token.type = TK_DGREAT;
		add_char(tokenizer);
		advance(tokenizer);
	}
	else
		tokenizer->token.type = TK_GREAT;
	add_char(tokenizer);
	return (get_next_token(tokenizer));
}

t_token	get_less(t_tokenizer *tokenizer)
{
	if (ft_isless(tokenizer->content[tokenizer->pos +1]))
	{
		tokenizer->token.type = TK_DLESS;
		add_char(tokenizer);
		advance(tokenizer);
	}
	else
		tokenizer->token.type = TK_LESS;
	add_char(tokenizer);
	return (get_next_token(tokenizer));
}

t_token	get_pipe(t_tokenizer *tokenizer)
{
	add_char(tokenizer);
	tokenizer->token.type = TK_PIPE;
	return (get_next_token(tokenizer));
}
