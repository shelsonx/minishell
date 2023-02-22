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

void	free_prompt(t_parser *parser_data)
{
	ft_free_nodes_env(&parser_data->commands);
	free_hashtable(parser_data->table_redirection);
	free(parser_data->prompt->line);
	free(parser_data->prompt->pwd);
	free(parser_data->prompt->prompt_str);
	free(parser_data->tokenizer->characteres);
	free(parser_data->tokenizer->content);
}

void	make_prompt_text(t_parser *parser_data)
{
	char	*tmp;
	char	*tmp2;
	char	*pwd_view;

	parser_data->prompt->text = "\033[1;31m 🎸MS𝄫: ";
	parser_data->prompt->pwd = getcwd(NULL, 0);
	pwd_view = ft_strrchr(parser_data->prompt->pwd, '/');
	if (pwd_view == NULL)
		pwd_view = "\033[0;33m 𝟒𝟐⑀⍴";
	tmp2 = ft_strjoin("\033[0;33m", pwd_view);
	tmp = ft_strjoin(parser_data->prompt->text, tmp2);
	parser_data->prompt->prompt_str = ft_strjoin(tmp, " 𝟒𝟐⑀⍴≫ \033[0m");
	free(tmp);
	free(tmp2);
}

void	free_signal(t_parser *parser)
{
	ft_free_nodes_env(&parser->builtin_vars->env2);
	ft_free_nodes_env(&parser->commands);
	free(parser->current_token);
	free(parser->tokenizer);
	free(parser->prompt->line);
	free(parser->prompt->prompt_str);
	free(parser->prompt->pwd);
	rl_clear_history();
}

void	run(t_parser *parser_data)
{
	while (true)
	{	
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sighandler);
		make_prompt_text(parser_data);
		parser_data->prompt->line = readline(parser_data->prompt->prompt_str);
		if (parser_data->prompt->line == NULL)
		{
			free_signal(parser_data);
			exit(EXIT_SUCCESS);
		}
		if (ft_strlen(parser_data->prompt->line) == 0)
		{
			free(parser_data->prompt->line);
			free(parser_data->prompt->pwd);
			free(parser_data->prompt->prompt_str);
			continue ;
		}
		add_history(parser_data->prompt->line);
		init_parser(parser_data);
		init_tokenizer(parser_data->tokenizer);
		parser(parser_data);
		execute(parser_data);
		free_prompt(parser_data);
	}
}

void	prompt(char **envp)
{
	t_parser		parser_data;
	t_builtin_vars	builtin_vars;
	t_prompt		prompt_s;

	parser_data.commands = NULL;
	init_env(&builtin_vars, envp);
	parser_data.builtin_vars = &builtin_vars;
	parser_data.prompt = &prompt_s;
	parser_data.tokenizer = malloc(sizeof(t_tokenizer));
	parser_data.tokenizer->content = NULL;
	parser_data.current_token = malloc(sizeof(t_token));
	run(&parser_data);
}
