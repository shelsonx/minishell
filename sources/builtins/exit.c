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

int	error_msg(char *declar, int status)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (status == 2)
	{
		ft_putstr_fd(declar, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (2);
	}
	else
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (1);
	}
	return (0);
}

static void	check_exit(char **declar, int declar_len)
{
	float	value;
	int		status_exit;

	status_exit = 0;
	if (ft_strcmp(declar[1], "-9223372036854775809") == 0)
	{
		ft_free_tab(declar);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (*(declar + 1) && check_str_nb(*(declar + 1)) == 0)
		status_exit = error_msg(*(declar + 1), 2);
	else if (declar_len > 2)
		status_exit = error_msg("", 1);
	if (status_exit > 0)
	{
		ft_free_tab(declar);
		exit(status_exit);
	}
	value = ft_atoi(*(declar + 1));
	if (value < -2147483648 || value > 2147483647
		|| ft_strcmp(declar[1], "-9223372036854775808") == 0)
	{
		ft_free_tab(declar);
		exit(0);
	}
	ft_free_tab(declar);
	if (value == 0)
	{
		error_msg(*declar, 2);
		value = 2;
	}
	exit((unsigned char)value);
}

void	ft_exit(char **declar)
{
	int		declar_len;

	declar_len = check_len(declar);
	if (declar_len == 1)
	{
		ft_free_tab(declar);
		exit(0);
	}
	else
		check_exit(declar, declar_len);
}
