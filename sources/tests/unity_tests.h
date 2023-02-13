#ifndef UNITY_TESTS
#define UNITY_TESTS
#include "../../includes/minishell.h"

typedef struct s_lines_tests
{
    char    *lines_minishell;
    char    *lines_shell;
}   t_lines_tests;

///aux
char    *get_join_lines(char *filename);
void    write_news_lines_minishell(char *path);
char    *get_lines(char *path);
void run_programs(char *command_minishell, char *command_shell, 
    char *out_minishell, char *out_shell, char **env);

t_lines_tests   *get_lines_tests(char *cmd_minishell, char *cmd_shell, 
    char *out_minishell, char *out_shell, char **env);

#endif