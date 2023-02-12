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
