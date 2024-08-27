#include "inc/minishell.h"

int main(int ac, char **av, char **env)
{
	t_minishell	sh;

	initialise_env (&sh.env, env);
	t_env *tmp = sh.env;
	while (tmp)
	{
		printf_fd (1, "%s \n", tmp->name);
		printf_fd (1, "%s \n", tmp->value);
		printf_fd (1, "%s \n", tmp->env);
		tmp = tmp->next;
	}
	// char **envp = lst_to_array(sh.env);
	// while (*envp)
	// {
	// 	printf_fd (1, "%s\n", *envp);
	// 	envp++;
	// }
}
