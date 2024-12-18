/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 02:45:23 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/18 02:49:17 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_wait(int l_pid, int r_pid, int *status)
{
	int	pid;

	while ((pid = wait(status)) > 0)
	{
		if (pid == l_pid || pid == r_pid)
		{
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					printf_fd(1, "\n");
				if (WTERMSIG(status) == SIGQUIT)
					printf_fd(1, "Quit: 3\n");
				return (128 + WTERMSIG(status));
			}
			return (WEXITSTATUS(status));
		}
	}
	return (0);
}

void	handle_sigint(int signal)
{
	if (signal == SIGINT && g_heredoc_signal == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	heredoc_sigint(int sig)
{
	(void)sig;
	g_heredoc_signal = 1;
	close(0);
	exit_status(1, 1);
}

void	signals_init(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	g_heredoc_signal = 0;
}
