#include "../../includes/minishell.h"

//-lreadline
//--suppressions=readline.supp

void    prompt(char **envp)
{
    t_parser parser_data;
    t_builtin_vars builtin_vars;
    parser_data.commands = NULL;

    init_env(&builtin_vars, envp);
	parser_data.builtin_vars = &builtin_vars;
    parser_data.current_token = malloc(sizeof(t_token));
    parser_data.tokenizer = malloc(sizeof(t_tokenizer));
    parser_data.tokenizer->content = NULL;
    char *tmp;

    t_prompt prompt_s;
    prompt_s.text = "🎸MINISHELL𝄫";
    
    parser_data.prompt = &prompt_s;

    while (true)
    {	
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sighandler);
        prompt_s.pwd = get_env_path("PWD", &builtin_vars);
        tmp = ft_strjoin(prompt_s.text, prompt_s.pwd);
        prompt_s.prompt_str = ft_strjoin(tmp, "$ ");
        free(tmp);
        prompt_s.line = readline(prompt_s.prompt_str);
        if(prompt_s.line == NULL) 
        {
            exit(0);
        }
        add_history(prompt_s.line);
        parser_data.tokenizer->content = ft_strdup(prompt_s.line);
        parser_data.index = 0;
        parser_data.commands = NULL;
        parser_data.index_redirect = 0;
        parser_data.table_redirection = create_table(1000);
        init_tokenizer(parser_data.tokenizer);
        parser(&parser_data);
        execute(&parser_data);
        ft_free_nodes(&parser_data.commands);
        free_hashtable(parser_data.table_redirection);
        free(prompt_s.line);
        free(prompt_s.pwd);
        free(prompt_s.prompt_str);
        free(parser_data.tokenizer->characteres);
        free(parser_data.tokenizer->content);
    }
}
