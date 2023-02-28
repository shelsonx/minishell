#include "../../includes/minishell.h"

int	is_quote_closed(t_tokenizer *tokenizer, char quote)
{
	while (tokenizer->current_char != quote)
	{
		if (tokenizer->current_char == '\0' || tokenizer->token.type == TK_EOF)
			return (false);
		add_char(tokenizer);
		advance(tokenizer);
	}
	if (ft_isalnum(tokenizer->content[tokenizer->pos + 1]))
	{
		advance(tokenizer);
		while (ft_isalpha(tokenizer->current_char))
		{
			add_char(tokenizer);
			advance(tokenizer);
		}
	}
	return (true);
}

int	check_quotes(t_tokenizer *tokenizer)
{
	char	quote;
	int		closed;

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

int	is_valid_identifier(t_tokenizer *tknz, int position)
{
	int		i;

	i = 0;
	while (i <= position)
	{
		if (tknz->characters[i] == '_' || ft_isalpha(tknz->characters[i]))
		{
			i++;
			while (tknz->characters[i] != '=')
			{
				if (!(tknz->characters[i] == '_'
						|| ft_isalnum(tknz->characters[i])))
					return (false);
				i++;
			}
		}
		i++;
	}
	return (true);
}

static void	set_identifier(t_tokenizer *tokenizer)
{
	while (!ft_strchr(METACHARS, tokenizer->current_char))
	{
		add_char(tokenizer);
		advance(tokenizer);
	}
}

void	tk_word(t_tokenizer *tokenizer)
{
	int		i;

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
			if (is_valid_identifier(tokenizer, i + 1))
			{
				set_identifier(tokenizer);
				tokenizer->token.type = TK_ASSIGNMENT_WORD;
				return ;
			}
		}
		if (tokenizer->token.type == TK_EOF)
			return ;
		i++;
	}
}
