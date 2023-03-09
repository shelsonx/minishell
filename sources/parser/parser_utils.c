/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjhony-x <sjhony-x@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:58:53 by sjhony-x          #+#    #+#             */
/*   Updated: 2023/03/07 16:59:02 by sjhony-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_parser(t_parser *parser_data)
{
	parser_data->tokenizer->content = ft_strdup(parser_data->prompt->line);
	parser_data->index = 0;
	parser_data->commands = NULL;
	parser_data->index_redirect = 0;
	parser_data->table_redirection = create_table(1000);
	parser_data->token_type = -1;
}

void	check_errors_pipe(t_parser *parser)
{
	if (parser->current_token->type == TK_ERROR
		|| parser->token_type == TK_PARENTHESIS
		|| parser->current_token->type == TK_PIPE)
	{
		if (parser->current_token->type == TK_PIPE)
		{
			free(parser->tokenizer->token.value);
			parser->tokenizer->token.value = NULL;
		}
		free_parser_error(parser);
		error(parser);
	}
}

void	check_errors_redirection(t_parser *parser, char *tokens)
{
	free(tokens);
	free_parser_error(parser);
	if (parser->current_token->type != TK_EOF
		&& parser->current_token->type != TK_PARENTHESIS)
	{
		free(parser->tokenizer->token.value);
		parser->tokenizer->token.value = NULL;
	}
	error(parser);
}
