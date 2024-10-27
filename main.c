/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 00:17:25 by orezkell          #+#    #+#             */
/*   Updated: 2024/10/28 00:18:32 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_minishell	sh;
	char		*input;

	(void)ac;
	(void)av;
	(void)env;
	initialise_env (&sh.env, env);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		add_history(input);
		parsing(&sh, input);
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