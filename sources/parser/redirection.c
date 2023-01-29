#include "../../includes/minishell.h"

t_token redirection_op(t_parser *parser)
{
    t_token current_token;

    current_token = *parser->current_token;
    if (current_token.type == TK_GREAT)
        parser->token_type = TK_GREAT;
    else if (current_token.type == TK_DGREAT)
        parser->token_type = TK_DGREAT;
    else if (current_token.type == TK_LESS)
        parser->token_type = TK_LESS;
    else if (current_token.type == TK_DLESS)
        parser->token_type = TK_DLESS;
    consume(parser);
    return (current_token);
}

void    set_redirect(t_parser *parser, char *tokens)
{
    tokens = ft_strjoin(tokens, " ");
    tokens = ft_strjoin(tokens, ft_itoa(parser->index));
    ht_insert(parser->table_redirection, ft_itoa(parser->index_redirect), tokens);
    parser->index_redirect++;
}

t_token redirection(t_parser *parser)
{
    t_token current_token;
    char    *tokens;

    tokens = ft_strdup("");
    current_token = redirection_op(parser);
    tokens = ft_strjoin(tokens, current_token.value);
    current_token = cmd_word(parser);
    tokens = ft_strjoin(tokens, " ");
    tokens = ft_strjoin(tokens, current_token.value);
    if (ft_strcmp(tokens, "") != 0)
        set_redirect(parser, tokens);
    return (current_token);
}
