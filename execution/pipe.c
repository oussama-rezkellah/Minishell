/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:37:29 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/17 10:45:21 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	execute_l_child(t_tree *cmd, int *pipe_fd, t_env *env)
{
	int	pid;

	if (!cmd)
		return (0);
	dprintf(2, "Left child\n");
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
	dprintf(2, "Right child\n");
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
	int		pid;

	(*env)->pipe_flag = 1;
	if (pipe(pipe_fd) < 0)
		return ;
	l_child = execute_l_child(node->l_child, pipe_fd, *env);
	r_child = execute_r_child(node->r_child, pipe_fd, *env);
	if (l_child < 0 || r_child < 0)
		return ;
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	while ((pid = wait(&status)) > 0)
	{
		if (pid == l_child || pid == r_child)
			exit_status(SET, WEXITSTATUS(status));
	}
	exit_status(SET, WEXITSTATUS(status));
}
