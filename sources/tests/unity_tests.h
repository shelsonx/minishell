#ifndef UNITY_TESTS
#define UNITY_TESTS
#include "../../includes/minishell.h"

///aux
char    *get_join_lines(char *filename);
void    write_news_lines_minishell(char *path);
char    *get_lines(char *path);
void run_programs(char *path_command, char *out_minishell, char *out_shell, char **env);

#endif