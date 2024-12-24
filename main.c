/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 00:17:25 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/24 14:15:44 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_minishell		sh;
	t_data			data;
	// struct termios	save;
	char			*input;
	extern int		rl_catch_signals;

	((void)ac), ((void)av);
	initialise_env (&sh.env, env);
	rl_catch_signals = 0;
	// if (isatty(0) && tcgetattr(0, &save))
	// 	return (perror("termios"), 1);
	while (1)
	{
		signals_init();
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (!input[0])
		{
			exit_status(SET, 0);
			continue ;
		}
		add_history(input);
		setup(INIT, &data);
		// sh.env->process_count = 0;
		// sh.env->fork_err = 0;
		if (!parsing(&sh, input))
		{
			ft_malloc (0, CLEAR);
			exit_status(SET, 258);
			continue ;
		}
		setup(FD_SET, &data);
		// sh.env->in_copy = dup(STDIN_FILENO);
		// sh.env->out_copy = dup(STDOUT_FILENO);
		open_all_heredocs(&sh);
		execution(sh.tree, &(sh.env), &data);
		setup(FD_BACK, &data);
		// dup2(sh.env->in_copy, STDIN_FILENO);
		// dup2(sh.env->out_copy, STDOUT_FILENO);
		close(data.in_copy);
		close(data.out_copy);
		// if (g_heredoc_signal != 1 && isatty(0) &&tcsetattr(0, TCSANOW, &save))
		// 	perror("termios");
		ft_malloc (0, CLEAR);
	}
	ft_malloc (0, CLEAR_ENV);
	return (exit_status(GET, 0));
}

