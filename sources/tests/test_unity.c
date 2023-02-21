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
    t_lines_tests *lines_tests = get_lines_tests(
        "files/commands/simple_command", "files/commands/simple_command", 
        "files/minishell/simple_command", "files/shell/simple_command",
        env);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(
        lines_tests->lines_shell, lines_tests->lines_minishell,
        ft_strlen(lines_tests->lines_shell));
}

void test_pipes(void)
{
    t_lines_tests *lines_tests = get_lines_tests(
        "files/commands/pipes", "files/commands/pipes", 
        "files/minishell/pipes", "files/shell/pipes",
        env);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(
        lines_tests->lines_shell, lines_tests->lines_minishell,
        ft_strlen(lines_tests->lines_shell));
}

void test_redirect_in(void)
{
    t_lines_tests *lines_tests = get_lines_tests(
       "files/commands/redirect_in", "files/commands/redirect_in", 
        "files/minishell/redirect_in", "files/shell/redirect_in",
        env);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(
        lines_tests->lines_shell, lines_tests->lines_minishell,
        ft_strlen(lines_tests->lines_shell));
}

void test_builtin_echo(void)
{
    t_lines_tests *lines_tests = get_lines_tests(
       "files/commands/builtin_echo", "files/commands/builtin_echo", 
        "files/minishell/builtin_echo", "files/shell/builtin_echo",
        env);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(
        lines_tests->lines_shell, lines_tests->lines_minishell,
        ft_strlen(lines_tests->lines_shell));
}

void test_expander(void)
{
    t_lines_tests *lines_tests = get_lines_tests(
       "files/commands/expander", "files/commands/expander", 
        "files/minishell/expander", "files/shell/expander",
        env);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(
        lines_tests->lines_shell, lines_tests->lines_minishell,
        ft_strlen(lines_tests->lines_shell));
}

int main(int argc, char **argv, char **envp)
{
    env = envp;
    UNITY_BEGIN();
    RUN_TEST(test_simple_command_ls);
    RUN_TEST(test_pipes);
    RUN_TEST(test_redirect_in);
    RUN_TEST(test_builtin_echo);
    RUN_TEST(test_expander);
    return UNITY_END();
}
