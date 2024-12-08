#include "../../inc/minishell.h"

int ft_ac(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int get_exit_status(char *string)
{
	int num;

	num = ft_atoi(string);
	if (ft_strlen (string) > 1 && (num == -1 || num == 0))
		return(printf_fd(2, "exit\n", ": numeric argument required\n"), 255);
	return ((unsigned char ) num);
}

int	spaces(char *string)
{
	int i;

	i = 0;
	while(string[i] && (string[i] >= 32 && string[i] <= '\t'))
		i++;
	if (string[i])
		return (1);
	return (0);
}

int	number(char *string)
{
	int i;

	i = 0;
	while(string[i] && (string[i] >= '0' && string[i] <= '9'))
		i++;
	if (string[i])
		return (1);
	return (0);
}

void	ft_exit(char **args)
{
	int  ac;

	ac = ft_ac(args);
	if (ac == 1)
	{
		printf_fd(2, "exit\n");
		ft_malloc (0, CLEAR);
		ft_malloc (0, CLEAR_ENV);
		exit(exit_status(GET, 0));
	}
	else if (ac > 1 && number(args[1]) || spaces(args[1]))
	{
		printf_fd(2, "exit: ", args[1], ": numeric argument required\n");
		ft_malloc (0, CLEAR);
		ft_malloc (0, CLEAR_ENV);
		exit(255);
	}
	else if (ac > 1 && !number(args[1]) || !spaces(args[1]))
	{
		ft_malloc (0, CLEAR);
		ft_malloc (0, CLEAR_ENV);
		exit(get_exit_status(args[1]));
	}
	else if (ac > 1 && !number(args[1]) || !spaces(args[1]))
		printf_fd(2, "exit\n", "exit: too many arguments\n");
}