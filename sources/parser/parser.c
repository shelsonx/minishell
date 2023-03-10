/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjhony-x <sjhony-x@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:59:00 by sjhony-x          #+#    #+#             */
/*   Updated: 2023/03/07 16:59:06 by sjhony-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_parser_error(t_parser *parser)
{
	ft_free_nodes_env(&parser->commands);
	free_hashtable(parser->table_redirection);
	free(parser->tokenizer->content);
	free(parser->tokenizer->characters);
	free(parser->prompt->line);
	free(parser->prompt->prompt_str);
	free(parser->prompt->pwd);
}

void	error(t_parser *parser_data)
{
	if (parser_data->tokenizer->token.type != TK_ERROR)
		ft_putendl_fd("syntax error near unexpected token", 2);
	run(parser_data);
}

void	consume(t_parser *parser)
{
	if (parser->current_token->type == parser->token_type)
	{
		free(parser->tokenizer->characters);
		parser->tokenizer->characters = ft_strdup("");
		*parser->current_token = next_token(parser->tokenizer);
	}
	else
		error(parser);
}

t_token	pipe_sequence(t_parser *parser)
{
	t_token	current_token;

	check_errors_pipe(parser);
	current_token = simple_command(parser);
	while (parser->current_token->type == TK_PIPE)
	{
		parser->token_type = TK_PIPE;
		free(parser->current_token->value);
		parser->current_token->value = NULL;
		consume(parser);
		current_token = simple_command(parser);
	}
	if (parser->token_type == TK_PIPE || parser->token_type == -1
		|| parser->current_token->type == TK_ERROR
		|| parser->current_token->type == TK_PARENTHESIS)
	{
		free_parser_error(parser);
		error(parser);
	}
	return (current_token);
}

void	parser(t_parser *parser)
{
	*parser->current_token = next_token(parser->tokenizer);
	pipe_sequence(parser);
	if (parser->current_token->type != TK_WORD
		&& parser->current_token->type != TK_EOF
		&& parser->current_token->type != TK_ASSIGNMENT_WORD)
		error(parser);
}
