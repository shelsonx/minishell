#include "../../includes/minishell.h"

t_token cmd_word(t_parser *parser)
{
    t_token current_token;

    current_token = *parser->current_token;
    parser->token_type = TK_WORD;
    return (current_token);
}

static void check_redirects(t_parser *parser)
{
    while (parser->current_token->type == TK_GREAT ||
        parser->current_token->type == TK_DGREAT ||
        parser->current_token->type == TK_LESS ||
        parser->current_token->type == TK_DLESS)
            redirection(parser);
}

static void check_word(t_parser *parser, t_token *current_token)
{
    while (parser->current_token->type == TK_WORD)
    {
        *current_token = cmd_word(parser);
        ft_add_back(&parser->commands, ft_new(parser->index, current_token->value));
        consume(parser);
    }
}

static void check_assignment_word(t_parser *parser, t_token *current_token)
{
    *current_token = *parser->current_token;
    parser->token_type = TK_ASSIGNMENT_WORD;
    ft_add_back(&parser->commands, ft_new(parser->index, current_token->value));
    consume(parser);
}

t_token simple_command(t_parser *parser)
{
    t_token current_token;

    current_token.value = "";
    check_redirects(parser);
    check_word(parser, &current_token);
    check_redirects(parser);
    check_word(parser, &current_token);
    if(parser->current_token->type == TK_ASSIGNMENT_WORD)
        check_assignment_word(parser, &current_token);
    if (ft_strcmp(current_token.value, "") != 0)
        parser->index++;
    return (current_token);
}
