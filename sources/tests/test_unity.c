#include "../../Unity/src/unity.h"
#include "../../includes/minishell.h"
#include "unity_tests.h"

char **env;

void setUp(void)
{
   //
}

void tearDown(void)
{
   //
}

void    write_news_lines_minishell(void)
{
    char *lines_minishell = get_join_lines("files/out_minishell");
    char *lines_origem = get_join_lines("files/out_shell");
    char **lines = ft_split(lines_minishell, '\n');
    
    int out_minishell;
    out_minishell = open("files/out_minishell", O_WRONLY | O_CREAT | O_TRUNC, 0777);
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

void test_execute_minishell(void)
{
    int fd_in;
    int fd_out;

    pid_t pid = fork();
    if (pid == 0)
    {
        char *args[] = {"/home/shelson/projects/minishell/minishell", NULL};
        fd_in = open("files/commands", O_RDONLY);
        fd_out = open("files/out_minishell", O_WRONLY | O_CREAT | O_TRUNC, 0777);
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
        fd_in = open("files/commands", O_RDONLY);
        fd_out = open("files/out_shell", O_WRONLY | O_CREAT | O_TRUNC, 0777);
        dup2(fd_in, STDIN_FILENO);
        dup2(fd_out, STDOUT_FILENO);
        execve(args[0], args, env);
    }
    close(fd_in);
    close(fd_out);
    waitpid(pid2, NULL, 0);


    if (pid != 0 && pid2 !=0)
    {
        write_news_lines_minishell();

        char *lines_minishell = get_lines("files/out_minishell");
        //debug manual
        dprintf(2, "minishell: %s\n", lines_minishell);
        char *lines_origem = get_lines("files/out_shell");
        //debug manual
        dprintf(2, "shell: %s\n", lines_origem);
        
        TEST_ASSERT_EQUAL_CHAR_ARRAY(lines_origem, lines_minishell, ft_strlen(lines_origem));
    }
}

int main(int argc, char **argv, char **envp)
{
    env = envp;
    UNITY_BEGIN();
    RUN_TEST(test_execute_minishell);
    return UNITY_END();
}
