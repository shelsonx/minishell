#include "../../includes/minishell.h"

void add_char(t_tokenizer *tokenizer)
{
    char    *old_characteres;
    char    current_char_p[2];

    old_characteres = tokenizer->characteres;
    current_char_p[0] = tokenizer->current_char;
    current_char_p[1] = '\0';
    tokenizer->characteres = ft_strjoin(tokenizer->characteres, current_char_p);
    free(old_characteres);
}

void    advance(t_tokenizer *tokenizer)
{
    tokenizer->pos++;
    if ((size_t)tokenizer->pos > ft_strlen(tokenizer->content))
        tokenizer->token.type = TK_EOF;
    else
        tokenizer->current_char = tokenizer->content[tokenizer->pos];
}

void    skip_space(t_tokenizer *tokenizer)
{
    while (ft_isspace(tokenizer->current_char) && (tokenizer->token.type != TK_EOF))
        advance(tokenizer);
}

int is_quote_closed(t_tokenizer *tokenizer, char quote)
{
    while (tokenizer->current_char != quote)
    {
        if (tokenizer->current_char == '\0' || tokenizer->token.type == TK_EOF)
            return (false);
        add_char(tokenizer);
        advance(tokenizer);
    }
    return (true);
}

int is_quote(char c)
{
    return (c == '\'' || c == '"');
}

int check_quotes(t_tokenizer *tokenizer)
{
    char    quote;
    int     closed;
    if (is_quote(tokenizer->current_char))
    {
        quote = tokenizer->current_char;
        add_char(tokenizer);
        advance(tokenizer);
        closed = is_quote_closed(tokenizer, quote);
        if (!closed)
        {
            ft_putendl_fd("Unclosed quotes!", 2);
            tokenizer->token.type = TK_ERROR;
            return (true);
        }
        add_char(tokenizer);
        advance(tokenizer);
        return (true);
    }
    return (false);
}

int is_valid_identifier(t_tokenizer *tknz, int position)
{
    int i;

    i = 0;
    while (i <= position)
    {
        if (tknz->characteres[i] == '_' || ft_isalpha(tknz->characteres[i]))
        {
            i++;
            while (tknz->characteres[i] != '=')
            {
                if (!(tknz->characteres[i] == '_' || ft_isalnum(tknz->characteres[i])))
                    return (false);
                i++;
            }
        }
        i++;
    }
    return (true);
}


void    tk_word(t_tokenizer *tokenizer)
{
    int i;

    i = 0;
    while (!ft_strchr(METACHARS, tokenizer->current_char))
    {
        if (check_quotes(tokenizer))
            return ;
        add_char(tokenizer);
        advance(tokenizer);
        if (tokenizer->current_char == '=' && i > 0)
        {
            add_char(tokenizer);
            advance(tokenizer);
            if (is_valid_identifier(tokenizer, i+1))
            {
                tokenizer->token.type = TK_ASSIGNMENT_WORD;
                return ;
            }
        }
        if (tokenizer->token.type == TK_EOF)
            return ;
        i++;
    }
}
