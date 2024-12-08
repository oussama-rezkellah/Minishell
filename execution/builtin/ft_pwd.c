#include "../../inc/minishell.h"

int ft_ac(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	get_current_working_directory(char **args)
{
	char *current;
	if (ft_ac(args) > 1)
	{
		printf_fd(2, "pwd: too many arguments\n");
		return ;
	}
	current = getcwd(NULL, 0);
	if (!current)
	{
		perror("getcwd: ");
		return ;
	}
	printf_fd(1, current, "\n");
	free(current);
}