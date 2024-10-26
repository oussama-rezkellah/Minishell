#include "inc/minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;

	t_minishell	sh;
	char	*input;

	initialise_env (&sh.env, env);
	// TEST for ENV

	// t_env *tmp = sh.env;
	// while (tmp)
	// {
	// 	printf_fd (1, "%s:", tmp->name);
	// 	printf_fd (1, "%s\n", tmp->value);
	// 	// printf_fd (1, "%s \n", tmp->env);
	// 	tmp = tmp->next;
	// }
	while (1)
	{
		input = readline("minishell$ ");
		printf ("%s\n", input);
		ft_malloc (0, CLEAR);
	}
	ft_malloc (0, CLEAR_ENV);
}
