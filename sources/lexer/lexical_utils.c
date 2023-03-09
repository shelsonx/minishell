/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:01:00 by progerio          #+#    #+#             */
/*   Updated: 2023/03/08 16:49:51 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_char(t_tokenizer *tokenizer)
{
	char	*old_characters;
	char	current_char_p[2];

	old_characters = tokenizer->characters;
	current_char_p[0] = tokenizer->current_char;
	current_char_p[1] = '\0';
	tokenizer->characters = ft_strjoin(tokenizer->characters, current_char_p);
	free(old_characters);
}

void	advance(t_tokenizer *tokenizer)
{
	tokenizer->pos++;
	if ((size_t)tokenizer->pos > ft_strlen(tokenizer->content))
		tokenizer->token.type = TK_EOF;
	else
		tokenizer->current_char = tokenizer->content[tokenizer->pos];
}

void	skip_space(t_tokenizer *tokenizer)
{
	while (ft_isspace(tokenizer->current_char)
		&& (tokenizer->token.type != TK_EOF))
		advance(tokenizer);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	trated_not_closed(t_tokenizer *tokenizer)
{
	ft_putendl_fd("Unclosed quotes!", 2);
	tokenizer->token.type = TK_ERROR;
	return (true);
}
