/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:37:29 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/21 06:07:22 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	execute_l_child(t_tree *cmd, int *pipe_fd, t_env *env)
{
	int	pid;

	if (!cmd)
		return (0);
	pid = fork();
	if (pid < 0)
		return (pid);
	else if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		execution(cmd, &env);
		exit(exit_status(GET, 0));
	}
	return (pid);
}

int	execute_r_child(t_tree *cmd, int *pipe_fd, t_env *env)
{
	int	pid;

	if (!cmd)
		return (0);
	pid = fork();
	if (pid < 0)
		return (pid);
	else if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		execution(cmd, &env);
		exit(exit_status(GET, 0));
	}
	return (pid);
}

void	pipe_exec(t_tree *node, t_env **env)
{
	int		l_child;
	int		r_child;
	int		pipe_fd[2];
	int		status;

	// (*env)->pipe_flag = 1;
	if (pipe(pipe_fd) < 0)
		return ;
	l_child = execute_l_child(node->l_child, pipe_fd, *env);
	r_child = execute_r_child(node->r_child, pipe_fd, *env);
	if (l_child < 0 || r_child < 0)
		return ;
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(l_child, NULL, 0);
	waitpid(r_child, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			printf_fd(1, "\n");
		else if (WTERMSIG(status) == SIGQUIT)
			printf_fd(1, "Quit: 3\n");
		status = (128 + WTERMSIG(status));
	}
	else
		status =  (WEXITSTATUS(status));
	exit_status(SET, status);
	// exit_status(SET, ft_wait(l_child, r_child, &status));
}

