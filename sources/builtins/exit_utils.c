#include "../../includes/minishell.h"

char	check_str_nb(char *declar)
{
	if (*declar == '+' || *declar == '-')
		declar++;
	while (*declar && (*declar >= '0' && *declar <= '9'))
		declar++;
	if (*declar == '\0')
		return (1);
	return (0);
}

int	check_len(char **declar)
{
	char	**len;

	len = declar;
	if (!declar)
		return (0);
	while (*len)
		len++;
	return (len - declar);
}
