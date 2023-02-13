#include "../../Unity/src/unity.h"
#include "../../includes/minishell.h"
#include "unity_tests.h"
//cc test_unity.c unity_tests.c ../../Unity/src/unity.c ../../libs/libft/libft.a
char **env;

void setUp(void)
{
   //
}

void tearDown(void)
{
   //
}

void test_simple_command_ls(void)
{
    char *out_minishell = "files/minishell/simple_command";
    char *out_shell = "files/shell/simple_command";
    run_programs("files/commands/simple_command", out_minishell, out_shell, env);
    write_news_lines_minishell(out_minishell);
    char *lines_minishell = get_lines(out_minishell);
    //debug manual
    //dprintf(2, "minishell: %s\n", lines_minishell);
    char *lines_origem = get_lines(out_shell);
    //debug manual
    //dprintf(2, "shell: %s\n", lines_origem);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(lines_origem, lines_minishell, ft_strlen(lines_origem));
}

void test_simple_command_pipes(void)
{
    char *out_minishell = "files/minishell/pipes";
    char *out_shell = "files/shell/pipes";
    run_programs("files/commands/pipes", out_minishell, out_shell, env);
    write_news_lines_minishell(out_minishell);
    char *lines_minishell = get_lines(out_minishell);
    //debug manual
    //dprintf(2, "minishell: %s\n", lines_minishell);
    char *lines_origem = get_lines(out_shell);
    //debug manual
    //dprintf(2, "shell: %s\n", lines_origem);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(lines_origem, lines_minishell, ft_strlen(lines_origem));
}

int main(int argc, char **argv, char **envp)
{
    env = envp;
    UNITY_BEGIN();
    RUN_TEST(test_simple_command_ls);
    RUN_TEST(test_simple_command_pipes);
    return UNITY_END();
}
