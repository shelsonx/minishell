/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: progerio <progerio@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:56:47 by progerio          #+#    #+#             */
/*   Updated: 2023/03/08 16:50:47 by progerio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libs/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define TRUE 1
# define FALSE 0
# define MININT -2147483648 
# define MAXINT 2147483647
# define CAPACITY 50000 // Size of the Hash Table
# define METACHARS	"|<>()\t "
# define INVALID_FD -2
# define FORKED 0

typedef struct s_token
{
	int		type;
	char	*value;
}	t_token;

typedef struct s_tokenizer
{
	char	current_char;
	int		pos;
	char	*content;
	char	*characters;
	t_token	token;
}	t_tokenizer;

typedef struct s_htitem		t_htitem;

struct s_htitem {
	char	*key;
	char	*value;
};

typedef struct s_linkedlist	t_linkedlist;

struct s_linkedlist {
	t_htitem		*item;
	t_linkedlist	*next;
};

typedef struct s_hashtable	t_hashtable;

struct s_hashtable {
	t_htitem		**items;
	t_linkedlist	**overflow_buckets;
	int				size;
	int				count;
};

typedef struct s_node
{
	int				index;
	char			*value;
	struct s_node	*next;
}	t_node;

typedef struct s_builtin_vars
{
	int				size;
	t_hashtable		*env;
	t_node			*env2;
	char			**redirection;
	int				i;
}	t_builtin_vars;

typedef struct s_prompt
{
	char	*line;
	char	*prompt_str;
	char	*text;
	char	*pwd;
}	t_prompt;

typedef struct s_parser
{
	t_tokenizer		*tokenizer;
	t_token			*current_token;
	int				token_type;
	int				index_redirect;
	int				index;
	struct s_data	*data;
	t_hashtable		*table_redirection;
	t_builtin_vars	*builtin_vars;
	t_node			*commands;
	t_prompt		*prompt;
}	t_parser;

typedef struct s_data {
	char			**pipeline;
	int				**fds;
	char			**args;
	int				fd_in;
	int				fd_out;
	int				*exit_status;
	t_builtin_vars	*builtin_vars;
	t_parser		*parser_data;
}	t_data;

typedef struct s_update_export
{
	char	**splitted_args;
	char	**splitted_ht_search;
	char	*tmp1;
	char	*tmp2;
	int		res1;
	int		res2;
}	t_update_export;

enum e_TOKENS
{
	TK_WORD,
	TK_ASSIGNMENT_WORD,
	TK_PARENTHESIS,
	TK_GREAT,
	TK_LESS,
	TK_DGREAT,
	TK_DLESS,
	TK_PIPE,
	TK_EOF,
	TK_ERROR
};

//builtin
char			*get_env_path(char *path, t_builtin_vars *builtin);
void			init_env(t_builtin_vars *builtin_vars, char **envp);
void			ft_env(t_builtin_vars *builtin_vars);
void			ft_pwd(void);
char			**get_env(t_builtin_vars *builtin_vars);
char			**get_builtins_names(void);
int				is_builtins(char *builtin_name);
int				handler_builtins(t_data *data);
void			ft_cd(t_data *data);

//builtins utils
void			free_ft_exit(t_data *data);

//unset
void			ft_unset(t_builtin_vars *builtins, char **args);
int				get_position(t_builtin_vars *builtins, char *arg);
void			del_pos(t_node **head, int position);

//exec builtins
int				exec_export(t_data *data);
int				exec_env(t_data *data);
int				exec_cd(t_data *data);
int				exec_pwd(t_data *data);
int				exec_unset(t_data *data);

//linked list env utils
t_node			*ft_new_env(int index, char	*value);
void			ft_free_nodes_env(t_node **lst);
char			*get_comparator(char *arg, int index);

//export
void			ft_export(t_builtin_vars *builtins, char **args);
int				contains_equal(char *args);

//export utils
int				is_valid_id(char *args);
int				env_exists(t_builtin_vars *builtins, char *args);

//export utils_2
int				to_update(t_builtin_vars *builtins, char *args);
void			add_env_path(t_builtin_vars *builtins, char *key, char *value);
void			insert_args_in_export(t_builtin_vars *builtins, char *args);

//export utils_3
int				contains_equal(char *args);
char			ft_isunderscore(char c);

//exit_utils
char			check_str_nb(char *declar);
int				check_len(char **declar);
void			trated_exits(char **declar, int status_exit, float *value);

//utils builtins
int				get_amount_builtins(t_parser *parser_data);
int				count_args(char **declar);
int				ft_echo(char **declar);
int				check_len(char **declar);
char			check_str_nb(char *declar);
int				error_msg(char *declar, int status);
void			ft_exit(char **declar);

//execute
char			**get_pipeline(t_data *data,
					t_parser *parser_data, int index_cmd);
int				execute(t_parser *parser_data);
char			*get_input_cmd(int position);

void			exec_only_one_command(t_data *data,
					t_parser *parser_data);
void			exec_two_commands(t_data *data,
					t_parser *parser_data, int total_commands);
void			exec_serveral_commands(t_data *data,
					t_parser *parser_data, int total_commands);

//execute utils
char			*get_exec_command(char *arg, t_builtin_vars *builtins);
int				**get_fd_close(void);
void			set_fd_close(int *fd);
void			wait_all_pids(t_parser *parser_data, int total_commands);
void			trated_builtin(t_data *data, int fd_out,
					char **input_cmd, int last);

//execute utils_2
void			open_files(t_parser *parser_data);
void			handler_cmds(t_data *data, t_parser *parser_data,
					int total_commands);
t_data			**get_data(void);
void			set_data(t_data *data);
void			wait_pid_one_command(t_data *data, pid_t child_pid);

//prompt
void			prompt(char **envp);
void			run(t_parser *parser_data);

//utils pipes
void			ft_free_fds(int **fds);
void			ft_close_fds(int **fds);

//paths
char			**get_paths_cmds(char *env_path);
char			**get_paths(t_builtin_vars *builtins);
char			*join_path_command(char *path, char *command);
char			**create_args(char **pipeline, t_builtin_vars *builtins);
int				is_full_path(char *arg, t_builtin_vars *builtins);

//children processes
pid_t			create_child_process(void);
pid_t			execute_child_process(t_data *data);
void			heredoc_children(
					t_parser *parser_data, int fd[], char **redirection);

//command
void			exec_one_command(t_data *data, int fd_in, int fd_out);
void			exec_first_command(t_data *data, int fd_in, int fd_out);
void			exec_middles_commands(t_data *data,
					t_parser *parser_data, int total_cmds_middles);
void			exec_last_command(t_data *data, int fd_in, int fd_out);
int				exists_commands(t_data *data);
int				get_fd_in(t_parser *parser_data, char *index_cmd);
int				get_fd_out(t_parser *parser_data, char *index_cmd);
void			here_doc(int fd[], char *limiter);

//redirects_utils
int				has_redirect(t_parser *parser_data,
					char *redirect, char *index_cmd);

void			set_fds_middle_cmd(t_data *data, t_parser *parser_data, int i);
void			set_fds_first_cmd(t_data *data, int fd_in, int fd_out);

//fds utils
int				set_in(t_parser *parser_data, char *index_cmd, int *fd_in);
int				set_out(t_parser *parser_data, char *index_cmd, int *fd_out);
int				set_fds(t_parser *parser_data, char *index_cmd,
					int *fd_in, int *fd_out);

//pipes
int				**create_pipes(int amount);

//signals
void			sighandler(int sigtype);

//exit program
void			exit_program(t_data *data);
void			error_command_msg(char **args, char *input_cmd);
void			free_children(t_parser *parser_data, char **redirection);
void			free_children_main(t_data *data, char **env);

//exit_program_utils
void			error_command_msg(char **args, char *input_cmd);

//get token
t_token			get_word(t_tokenizer *tokenizer);
t_token			get_parenthesis(t_tokenizer *tokenizer);
t_token			get_great(t_tokenizer *tokenizer);
t_token			get_less(t_tokenizer *tokenizer);
t_token			get_pipe(t_tokenizer *tokenizer);

//lexical analyzer
char			*get_name_token(int type_token);
int				is_eof(size_t *pos, char *content);
void			init_tokenizer(t_tokenizer *tokenizer);
t_token			get_next_token(t_tokenizer *tokenizer);
t_token			next_token(t_tokenizer *tokenizer);

//lexical resources

void			invalid_token(t_tokenizer *tokenizer);
void			tk_word(t_tokenizer *tokenizer);

//lexica utils
void			add_char(t_tokenizer *tokenizer);
void			skip_space(t_tokenizer *tokenizer);
void			advance(t_tokenizer *tokenizer);
int				is_quote(char c);
int				trated_not_closed(t_tokenizer *tokenizer);

//parser
void			parser(t_parser *parser);
t_token			*cmd_word(t_parser *parser);
t_token			simple_command(t_parser *parser);
void			consume(t_parser *parser);
void			error(t_parser *parser_data);
t_token			*redirection(t_parser *parser);
t_token			*redirection_op(t_parser *parser);
void			free_parser_error(t_parser *parser);

//parser utils
void			init_parser(t_parser *parser_data);
void			check_errors_pipe(t_parser *parser);
void			check_errors_redirection(t_parser *parser, char *tokens);

//expander
void			expander(char **args, t_builtin_vars *builtin_vars,
					t_data *data);
int				expand_simple_quotes(char **args, t_builtin_vars *builtin_vars);
int				expand_double_quotes(char **args, t_builtin_vars *builtin_vars);
int				get_amount_character(char **args, char character);
void			free_lines_prompt(t_parser *parser_data);

//quotes
void			remove_quotes(char **args);

//quotes utils
int				contains_quotes(char *arg);
void			remove_sides(char quote[], char **args, int x);
void			set_special_char(t_data *data, char **args, int x);
int				is_only_space(const char *characters);

//linked list functions
t_node			*ft_last(t_node *lst);
void			ft_add_back(t_node **lst, t_node *new_node);
void			ft_add_front(t_node **lst, t_node *new_node);
int				ft_size(t_node *lst);
t_node			*ft_new(int index, char	*value);
void			ft_free_nodes(t_node **lst);

//ht_functions
unsigned long	hash_function(char *str);
t_htitem		*create_item(char *key, char *value);
void			free_item(t_htitem *item);
void			handle_collision(t_hashtable *table,
					unsigned long index, t_htitem *item);
void			ht_delete(t_hashtable *table, char *key);

//ht_utils
t_hashtable		*create_table(int size);
void			ht_insert(t_hashtable *table, char *key, char *value);
char			*ht_search(t_hashtable *table, char *key);

//free_ht
void			free_hashtable(t_hashtable *table);

//linkedlist_utils
t_linkedlist	*allocate_list(void);
t_linkedlist	*linkedlist_insert(t_linkedlist *list, t_htitem *item);
void			free_linkedlist(t_linkedlist *list);

//overflow_buckets
t_linkedlist	**create_overflow_buckets(t_hashtable *table);
void			free_overflow_buckets(t_hashtable *table);

//exit status
int				get_exit_status(char *arg, t_builtin_vars *builtins);

//sort queue
int				sort_queue(t_node **head, int count);
#endif /* MINISHELL */
