/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 00:17:25 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/19 22:35:43 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_minishell		sh;
	struct termios	save;
	char			*input;


	(void)ac;
	(void)av;
	(void)env;
	initialise_env (&sh.env, env);
	// t_env *tmp = sh.env;
	// while (tmp)
	// {
	// 	printf_fd (1, "%s:", tmp->name);
	// 	printf_fd (1, "%s\n", tmp->value);
	// 	printf_fd (1, "%s \n", tmp->env);
	// 	tmp = tmp->next;
	// }
	// exit(0);
	rl_catch_signals = 0;
	if (isatty(0) && tcgetattr(0, &save))
		return (perror("termios"), 1);
	while (1)
	{
		signals_init();
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (!input[0])
			continue ;




		add_history(input);
		if (!parsing(&sh, input))
		{
			ft_malloc (0, CLEAR);
			continue ;
		}

		int in_copy = dup(STDIN_FILENO);
		int out_copy = dup(STDOUT_FILENO);

		open_all_heredocs(&sh);
		execution(sh.tree, &(sh.env));
		dup2(in_copy, STDIN_FILENO);
		dup2(out_copy, STDOUT_FILENO);
		close(in_copy);
		close(out_copy);
		if (g_heredoc_signal != 1 && isatty(0) && tcsetattr(0, TCSANOW, &save))
			perror("termios");
		ft_malloc (0, CLEAR);
	}
	ft_malloc (0, CLEAR_ENV);
}

	// TEST for ENV

	// t_env *tmp = sh.env;
	// while (tmp)
	// {
	// 	printf_fd (1, "%s:", tmp->name);
	// 	printf_fd (1, "%s\n", tmp->value);
	// 	// printf_fd (1, "%s \n", tmp->env);
	// 	tmp = tmp->next;
	// }
