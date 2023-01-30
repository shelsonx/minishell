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
    return (current_token);
}

void    set_redirect(t_parser *parser, char *tokens)
{
    char    *tmp;

    tmp = tokens;
    tokens = ft_strjoin(tokens, " ");
    free(tmp);
    tmp = tokens;
    tokens = ft_strjoin(tokens, get_input_cmd(parser->index));
    free(tmp);
    ht_insert(parser->table_redirection, get_input_cmd(parser->index_redirect), tokens);
    parser->index_redirect++;
    free(tokens);
}

t_token redirection(t_parser *parser)
{
    t_token current_token;
    char    *tokens;
    char    *tmp;

    tokens = ft_strdup("");
    current_token = redirection_op(parser);
    tmp = tokens;
    tokens = ft_strjoin(tokens, current_token.value);
    free(tmp);
    consume(parser);
    current_token = cmd_word(parser);
    tmp = tokens;
    tokens = ft_strjoin(tokens, " ");
    free(tmp);
    tmp = tokens;
    tokens = ft_strjoin(tokens, current_token.value);
    free(tmp);
    if (ft_strcmp(tokens, "") != 0)
        set_redirect(parser, tokens);
    return (current_token);
}
