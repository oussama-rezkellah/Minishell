/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 02:45:23 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/24 13:49:44 by aben-hss         ###   ########.fr       */
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

void	setup(t_flag flag, t_data *data)
{
	if (flag == FD_SET)
	{
		data->in_copy = dup(STDIN_FILENO);
		data->out_copy = dup(STDOUT_FILENO);
	}
	else if (flag == FD_BACK)
	{
		dup2(data->in_copy, STDIN_FILENO);
		dup2(data->out_copy, STDOUT_FILENO);
	}
	else if (flag == INIT)
	{
		data->process_count = 0;
		data->fork_err = 0;
	}
}
