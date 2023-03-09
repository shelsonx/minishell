/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:00:02 by sjhony-x          #+#    #+#             */
/*   Updated: 2023/03/08 16:50:04 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_prompt(t_parser *parser_data)
{
	ft_free_nodes_env(&parser_data->commands);
	free_hashtable(parser_data->table_redirection);
	free(parser_data->prompt->line);
	free(parser_data->prompt->pwd);
	free(parser_data->prompt->prompt_str);
	free(parser_data->tokenizer->characters);
	free(parser_data->tokenizer->content);
}

void	make_prompt_text(t_parser *parser_data)
{
	char	*tmp;
	char	*tmp2;
	char	*pwd_view;

	parser_data->prompt->text = "\001\e[1m\e[31m\002 🎸MS ";
	parser_data->prompt->pwd = getcwd(NULL, 0);
	pwd_view = ft_strrchr(parser_data->prompt->pwd, '/');
	if (pwd_view == NULL)
		pwd_view = "\001\e[33m\002 𝟒𝟐⑀⍴";
	tmp2 = ft_strjoin("\001\e[33m\002", pwd_view);
	tmp = ft_strjoin(parser_data->prompt->text, tmp2);
	parser_data->prompt->prompt_str = ft_strjoin(
			tmp, "\001\e[1m\e[31m\002 𝄫: \001\033\e[0m\002");
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
		if (ft_strlen(parser_data->prompt->line) == 0
			|| is_only_space(parser_data->prompt->line))
		{
			free_lines_prompt(parser_data);
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
