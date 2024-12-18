/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:13:26 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/18 03:26:42 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_heredoc(char *del, t_env *env)
{
	int		fd[2];
	char	*line;
	char	*newline;
	int		fd_in;
	// int		flag;

	(void)env;
	// flag = 1;
	fd_in = dup(0);
	if (pipe(fd) == -1)
		return (-1);
	signal(SIGINT, heredoc_sigint);
	// determine expand flag
	// del = expand_flag(del, &flag);
	while (1)
	{
		line = readline("> ");
		if (g_heredoc_signal)
			break ;
		if (!line || !ft_strcmp(line, del))
			return (free(line), close(fd_in), close(fd[1]), fd[0]);
		// TODO logic for heredoc expansion
		// if (!flag)
		// 	newline = expand_heredoc(line, env);
		// else
			newline = line;
		if (!newline)
			newline = "";
		write(fd[1], newline, ft_strlen(newline));
		write(fd[1], "\n", 1);
		free(line);
	}
	if (g_heredoc_signal == 1)
		return ((dup2(fd_in, 0), close(fd_in), free(line), close(fd[1]),
				close(fd[0]), -2));
	return (free(line), close(fd[1]), fd[0]);
}

int	handle_exec_err(char *cmd, int errno_val)
{
	printf_fd(2, "minishell: ");
	printf_fd(2, cmd);
	printf_fd(2, ": ");
	if (errno_val == -69)
		return (printf_fd(2, "cd: error retrieving current directory: \
		getcwd: cannot access parent directories: No such file or \
		directory\n"), 1);
	if (errno_val == -127)
		return (printf_fd(2, "command not found\n"), 127);
	else if (errno_val == EACCES)
		return (printf_fd(2, "permission denied\n"), 126);
	else
		return (printf_fd(2, "%s\n", strerror(errno_val)));
}

int	handle_redirections(t_tree *node)
{
	if (node->fd_in != STDIN_FILENO)
	{
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
		{
			return (-1);
		}
		close(node->fd_in);
	}
	if (node->fd_out != STDOUT_FILENO)
	{
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
		{
			return (-1);
		}
		close(node->fd_out);
	}
	return (0);
}
