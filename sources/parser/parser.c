#include "../../includes/minishell.h"

void    error(t_parser *parser_data)
{
    if (parser_data->tokenizer->token.type != TK_ERROR)
        ft_printf("syntax error near unexpected token `newline'\n");
    prompt(get_env(parser_data->builtin_vars));
}

void    consume(t_parser *parser)
{
    if (parser->current_token->type == parser->token_type)
    {
        free(parser->tokenizer->characteres);
        parser->tokenizer->characteres = ft_strdup("");
        *parser->current_token = next_token(parser->tokenizer);
    }
    else
        error(parser);
}

t_token pipe_sequence(t_parser *parser)
{
    t_token current_token;

    current_token = simple_command(parser);
    while (parser->current_token->type == TK_PIPE)
    {
        parser->token_type = TK_PIPE;
        consume(parser);
        current_token = simple_command(parser);
    }
    if(parser->token_type == TK_PIPE)
        error(parser);
    return (current_token);
}

void    parser(t_parser *parser)
{
    *parser->current_token = next_token(parser->tokenizer);
    pipe_sequence(parser);
    if (parser->current_token->type != TK_WORD && 
        parser->current_token->type != TK_EOF && 
        parser->current_token->type != TK_ASSIGNMENT_WORD)
        error(parser);
}
