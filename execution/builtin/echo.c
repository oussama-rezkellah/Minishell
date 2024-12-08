#include "../../inc/minishell.h"

int is_valid(char *arg)
{
	int i = 0;
	if (arg[i] == '-')
		i++;
	else 
		return (1);
	while (arg[i] == 'n')
		i++;
	if (arg[i])
		return (1);
	return (0);
}

void ft_echo(char **args)
{
	int i;
	int check;

	i = 0;
	check = 0;
	if (!args[1])
	{
		printf_fd(1, "\n");
		return ;
	}
	if (args && args[i])
	{
		while (!is_valid(&args[i]) && ++check)
			i++;
	}
	while (args[i])
	{
		printf_fd(1, args[i++]);
		if (args[i])
			printf(" ");
	}
	if (!check)
		printf("\n");
}
