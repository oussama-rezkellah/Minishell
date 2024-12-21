/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:13:26 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/21 18:10:04 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_heredoc(char *del, t_env *env)
{
	int		fd[2];
	char	*line;
	char	*newline;
	int		fd_in;
	int		flag;

	(void)env;
	flag = 1;
	fd_in = dup(0);
	if (pipe(fd) == -1)
		return (-1);
	signal(SIGINT, heredoc_sigint);
	del = expand_del(del, &flag);
	while (1)
	{
		line = readline("> ");
		if (g_heredoc_signal == 1)
			break ;
		if (!line || !ft_strcmp(line, del))
			return (free(line), close(fd_in), close(fd[1]), fd[0]);
		if (!flag)
			newline = expand_heredoc(line, env);
		else
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

int	handle_redirections(t_tree *node)
{
	if (node->fd_in != STDIN_FILENO)
	{
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
		{
			return (handle_exec_err("dup2: ", errno), -1);
		}
		close(node->fd_in);
	}
	if (node->fd_out != STDOUT_FILENO)
	{
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
		{
			return (handle_exec_err("dup2: ", errno), -1);
		}
		close(node->fd_out);
	}
	return (0);
}
