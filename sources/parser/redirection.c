/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjhony-x <sjhony-x@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:59:08 by sjhony-x          #+#    #+#             */
/*   Updated: 2023/03/07 16:59:09 by sjhony-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_redirection(t_token *current_token)
{
	free(current_token->value);
	current_token->value = NULL;
	free(current_token);
	current_token = NULL;
}

t_token	*redirection_op(t_parser *parser)
{
	t_token	*current_token;

	current_token = malloc(sizeof(t_token));
	current_token->value = ft_calloc(ft_strlen(
				parser->current_token->value) + 1, sizeof(char));
	current_token->type = parser->current_token->type;
	ft_strcpy(current_token->value, parser->current_token->value);
	if (current_token->type == TK_GREAT)
		parser->token_type = TK_GREAT;
	else if (current_token->type == TK_DGREAT)
		parser->token_type = TK_DGREAT;
	else if (current_token->type == TK_LESS)
		parser->token_type = TK_LESS;
	else if (current_token->type == TK_DLESS)
		parser->token_type = TK_DLESS;
	return (current_token);
}

void	set_redirect(t_parser *parser, char *tokens)
{
	char	*tmp;
	char	join[2];

	join[0] = 127;
	join[1] = '\0';
	tmp = tokens;
	tokens = ft_strjoin(tokens, join);
	free(tmp);
	tmp = tokens;
	tokens = ft_strjoin(tokens, get_input_cmd(parser->index));
	free(tmp);
	ht_insert(parser->table_redirection, get_input_cmd(
			parser->index_redirect), tokens);
	parser->index_redirect++;
	free(tokens);
}

void	check_filename(t_token *current_token,
			t_parser *parser, char **tmp, char **tokens)
{
	char	join[2];

	join[0] = 127;
	join[1] = '\0';
	current_token = cmd_word(parser);
	*tmp = *tokens;
	*tokens = ft_strjoin(*tokens, join);
	free(*tmp);
	*tmp = *tokens;
	*tokens = ft_strjoin(*tokens, current_token->value);
	free_redirection(current_token);
	free(parser->current_token->value);
	parser->current_token->value = NULL;
	consume(parser);
	free(*tmp);
}

t_token	*redirection(t_parser *parser)
{
	t_token	*current_token;
	char	*tokens;
	char	*tmp;

	tokens = ft_strdup("");
	current_token = redirection_op(parser);
	tmp = tokens;
	tokens = ft_strjoin(tokens, current_token->value);
	free(tmp);
	free_redirection(current_token);
	free(parser->current_token->value);
	parser->current_token->value = NULL;
	consume(parser);
	if (parser->current_token->type != TK_WORD)
		check_errors_redirection(parser, tokens);
	check_filename(current_token, parser, &tmp, &tokens);
	if (ft_strcmp(tokens, "") != 0)
		set_redirect(parser, tokens);
	return (current_token);
}
