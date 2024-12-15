
#include "../../inc/minishell.h"

int	flag_check(char *str)
{
	int	j;

	j = 0;
	if (!str || !*str)
		return (-1);
	if (str[j] == '-')
		j++;
	while (str[j] == 'n')
		j++;
	if (str[j] == '\0')
		return (1);
	return (0);
}

int	echo_cmd(char **arg)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if (!arg)
		return (0);
	if (!arg[i] || !arg[i][0])
		return (printf_fd(1, "\n"), 0);
	while (flag_check(arg[i]))
	{
		flag = 1;
		i++;
	}
	while (arg[i])
	{
		printf_fd(1, "%s", arg[i]);
		if (arg[i + 1])
			printf_fd(1, " ");
		i++;
	}
	if (!flag)
		printf_fd(1, "\n");
	return (0);
}