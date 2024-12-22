/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 00:17:25 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/22 01:17:00 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_minishell		sh;
	struct termios	save;
	char			*input;
	extern int		rl_catch_signals;

	(void)ac;
	(void)av;
	(void)env;
	initialise_env (&sh.env, env);
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
		sh.env->process_count = 0;
		sh.env->fork_err = 0;
		if (!parsing(&sh, input))
		{
			ft_malloc (0, CLEAR);
			exit_status(SET, 258);
			continue ;
		}
		sh.env->in_copy = dup(STDIN_FILENO);
		sh.env->out_copy = dup(STDOUT_FILENO);
		open_all_heredocs(&sh);
		execution(sh.tree, &(sh.env));
		dup2(sh.env->in_copy, STDIN_FILENO);
		dup2(sh.env->out_copy, STDOUT_FILENO);
		close(sh.env->in_copy);
		close(sh.env->out_copy);
		if (g_heredoc_signal != 1 && isatty(0) &&tcsetattr(0, TCSANOW, &save))
			perror("termios");
		ft_malloc (0, CLEAR);
	}
	ft_malloc (0, CLEAR_ENV);
}

