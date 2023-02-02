#include "../../includes/minishell.h"

//-lreadline
//--suppressions=readline.supp

void    init_parser(t_parser *parser_data)
{
    parser_data->tokenizer->content = ft_strdup(parser_data->prompt->line);
    parser_data->index = 0;
    parser_data->commands = NULL;
    parser_data->index_redirect = 0;
    parser_data->table_redirection = create_table(1000);
}

void    free_prompt(t_parser *parser_data)
{
    ft_free_nodes(&parser_data->commands);
    free_hashtable(parser_data->table_redirection);
    free(parser_data->prompt->line);
    free(parser_data->prompt->pwd);
    free(parser_data->prompt->prompt_str);
    free(parser_data->tokenizer->characteres);
    free(parser_data->tokenizer->content);
}

void    make_prompt_text(t_parser *parser_data)
{
    char *tmp;

    parser_data->prompt->text = "🎸MINISHELL𝄫";
    parser_data->prompt->pwd = get_env_path("PWD", parser_data->builtin_vars);
    tmp = ft_strjoin(parser_data->prompt->text, parser_data->prompt->pwd);
    parser_data->prompt->prompt_str = ft_strjoin(tmp, "$ ");
    free(tmp);
}

void    run(t_parser *parser_data)
{
    while (true)
    {	
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sighandler);
        make_prompt_text(parser_data);
        parser_data->prompt->line = readline(parser_data->prompt->prompt_str);
        if(parser_data->prompt->line == NULL) 
        {
            exit(0);
        }
        add_history(parser_data->prompt->line);
        init_parser(parser_data);
        init_tokenizer(parser_data->tokenizer);
        parser(parser_data);
        execute(parser_data);
        free_prompt(parser_data);
    }
}

void    prompt(char **envp)
{
    t_parser parser_data;
    t_builtin_vars builtin_vars;
    t_prompt prompt_s;
    
    parser_data.commands = NULL;
    init_env(&builtin_vars, envp);
	parser_data.builtin_vars = &builtin_vars;
    parser_data.prompt = &prompt_s;
    parser_data.tokenizer = malloc(sizeof(t_tokenizer));
    parser_data.tokenizer->content = NULL;
    parser_data.current_token = malloc(sizeof(t_token));
    run(&parser_data);
}
