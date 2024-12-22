/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:37:29 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/22 06:24:34 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_fork(t_env *env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (exit(1), -1);
	env->process_count++;
	if (env->process_count > 25)
		env->fork_err = 1;
	return (pid);
}

int	execute_l_child(t_tree *cmd, int *pipe_fd, t_env *env)
{
	int	pid;

	if (!cmd)
		return (0);
	pid = ft_fork(env);
	if (pid < 0)
		return (exit(1), pid);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
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
	pid = ft_fork(env);
	if (pid < 0)
		return (exit(1), pid);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
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
	int (l_child), (r_child), (pipe_fd[2]), (status);
	if (pipe(pipe_fd) < 0)
		return ;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
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
		status = (WEXITSTATUS(status));
	exit_status(SET, status);
}
