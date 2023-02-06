#include "../../includes/minishell.h"

t_token *cmd_word(t_parser *parser)
{
    t_token *current_token;

    current_token = malloc(sizeof(t_token));
    current_token->value = ft_calloc(ft_strlen(parser->current_token->value) + 1, sizeof(char));
    current_token->type = parser->current_token->type;
    ft_strcpy(current_token->value, parser->current_token->value);
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
        current_token = cmd_word(parser);
        ft_add_back(&parser->commands, ft_new_env(parser->index, current_token->value));
        free(parser->current_token->value);
        parser->current_token->value = NULL;
        consume(parser);
        free(current_token->value);
        current_token->value = NULL;
        free(current_token);
        current_token = NULL;
    }
}

static void check_assignment_word(t_parser *parser, t_token *current_token)
{
    *current_token = *parser->current_token;
    parser->token_type = TK_ASSIGNMENT_WORD;
    ft_add_back(&parser->commands, ft_new_env(parser->index, current_token->value));
    free(current_token->value);
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
    while(parser->current_token->type == TK_ASSIGNMENT_WORD)
        check_assignment_word(parser, &current_token);
    //if (ft_strcmp(current_token.value, "") != 0)
        parser->index++;
    return (current_token);
}
