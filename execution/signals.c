/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 02:45:23 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/22 06:52:10 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_sigint(int signal)
{
	if (signal == SIGINT && g_heredoc_signal == 0)
	{
		printf_fd(1, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit_status(SET, 1);
	}
}

void	heredoc_sigint(int sig)
{
	(void)sig;
	g_heredoc_signal = 1;
	close(0);
	exit_status(SET, 1);
}

void	signals_init(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	g_heredoc_signal = 0;
}
