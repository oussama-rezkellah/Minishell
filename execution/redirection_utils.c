/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:13:26 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/24 22:12:47 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void clean_heredoc(t_tree *node)
{
	t_redir	*redir;

	redir = node->redir;
	while (redir)
	{
		if (redir->type == HEREDOC)
			close(redir->fd);
		redir = redir->next;
	}
	node->redir = NULL;
}

static int	handle_heredoc_line(char *del, int *fd, t_env *env, int flag)
{
	char	*line;
	char	*newline;

	line = readline("> ");
	if (g_heredoc_signal == 1)
		return (1);
	if (!line || !ft_strcmp(line, del))
		return (free(line), 2);
	if (!flag)
		newline = expand_heredoc(line, env);
	else
		newline = line;
	if (!newline)
		newline = "";
	write(fd[1], newline, ft_strlen(newline));
	write(fd[1], "\n", 1);
	free(line);
	return (0);
}

int	ft_heredoc(char *del, t_env *env)
{
	int	fd[2];
	int	fd_in;
	int	flag;
	int	status;

	flag = 0;
	fd_in = dup(0);
	if (pipe(fd) == -1)
		return (-1);
	signal(SIGINT, heredoc_sigint);
	del = expand_del(del, &flag);
	while (1)
	{
		status = handle_heredoc_line(del, fd, env, flag);
		if (status == 1)
			return ((dup2(fd_in, 0), close(fd_in), close(fd[1]),
					close(fd[0]), -2));
		if (status == 2)
			return (close(fd_in), close(fd[1]), fd[0]);
	}
	return (close(fd[1]), fd[0]);
}

int	handle_redirections(t_tree *node)
{
	if (node->fd_in != STDIN_FILENO)
	{
		if (dup2(node->fd_in, STDIN_FILENO) == -1)
			return (-1);
		close(node->fd_in);
	}
	if (node->fd_out != STDOUT_FILENO)
	{
		if (dup2(node->fd_out, STDOUT_FILENO) == -1)
			return (-1);
		close(node->fd_out);
	}
	return (0);
}
