#include "unity_tests.h"
#include "../../includes/minishell.h"

char    *get_join_lines(char *filename)
{
    int file_fd;
    char *line;
    char *lines;

    line = ft_strdup("");
    lines = ft_strdup("");
    file_fd = open(filename, O_RDONLY, 0777);
    while (line = ft_get_next_line(file_fd))
        lines = ft_strjoin(lines, line);
    close(file_fd);
    return lines;
}

void    write_news_lines_minishell(char *path)
{
    char *lines_minishell = get_join_lines(path);
    char **lines = ft_split(lines_minishell, '\n');
    
    int out_minishell;
    out_minishell = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    int x = 1;
    while (x < ft_len_rows_tab(lines)-1)
    {
        ft_putendl_fd(lines[x], out_minishell);
        x++;
    }
    close(out_minishell);
}

char    *get_lines(char *path)
{
    FILE *fd_minishell = fopen(path, "r");
    char line[255];
    char    *lines = ft_strdup("");
    while (fgets(line, 255, fd_minishell))
        lines = ft_strjoin(lines, line);
    fclose(fd_minishell);
    return (lines);
}

void run_programs(char *command_minishell, char *command_shell, 
    char *out_minishell, char *out_shell, char **env)
{
    int fd_in;
    int fd_out;

    pid_t pid = fork();
    if (pid == 0)
    {
        char *args[] = {"/home/shelson/projects/minishell/minishell", NULL};
        fd_in = open(command_minishell, O_RDONLY);
        fd_out = open(out_minishell, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        dup2(fd_in, STDIN_FILENO);
        dup2(fd_out, STDOUT_FILENO);
        execve(args[0], args, env);
    }
    close(fd_in);
    close(fd_out);
    waitpid(pid, NULL, 0);

    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        char *args[] = {"/bin/bash",  NULL};
        fd_in = open(command_shell, O_RDONLY);
        fd_out = open(out_shell, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        dup2(fd_in, STDIN_FILENO);
        dup2(fd_out, STDOUT_FILENO);
        execve(args[0], args, env);
    }
    close(fd_in);
    close(fd_out);
    waitpid(pid2, NULL, 0);
}

t_lines_tests   *get_lines_tests(char *cmd_minishell, char *cmd_shell, 
    char *out_minishell, char *out_shell, char **env)
{
    run_programs(cmd_minishell, cmd_shell, 
        out_minishell, out_shell, env);
    write_news_lines_minishell(out_minishell);
    t_lines_tests *lines_tests = malloc(sizeof(t_lines_tests *));
    lines_tests->lines_minishell = get_lines(out_minishell);
    lines_tests->lines_shell = get_lines(out_shell);;
    return (lines_tests);
}
