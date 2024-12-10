/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:05:33 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/10 22:55:35 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_exec_err(char *cmd, int errno_val)
{
	printf_fd(2, "minishell: ");
	printf_fd(2, cmd);
	printf_fd(2, ": ");
	if (errno_val == ENOENT)
		return (printf_fd(2, "command not found\n"), 127);
	else if (errno_val == EACCES)
		return (printf_fd(2, "permission denied\n"), 126);
	else
		return (printf_fd(2, strerror(errno_val)), 1);
}

int	is_infile(t_redir *redirect)
{
	t_redir	*temp;

	temp = redirect;
	if (temp->type == IN || temp->type == HEREDOC)
		return (1);
	return (0);
}

int	is_outfile(t_redir *redirect)
{
	t_redir	*temp;

	temp = redirect;
	if (temp->type == OUT || temp->type == APPEND)
		return (1);
	return (0);
}

int	handle_outfile(t_tree *cmd, t_redir *current)
{
	int	fd;

	fd = -1;
	if (current->type == OUT)
	{
		fd = open(current->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			return (handle_exec_err(current->file, errno), -1);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		cmd->fd_out = fd;
	}
	else if (current->type == APPEND)
	{
		fd = open(current->file, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (handle_exec_err(current->file, errno), -1);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		cmd->fd_out = fd;
	}
	return (1);
}

int	handle_infile(t_tree *cmd, t_redir *current)
{
	int	fd;

	fd = -1;
	if (current->type == IN)
	{
		fd = open(current->file, O_RDONLY);
		if (fd == -1)
			return (handle_exec_err(current->file, errno), -1);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		cmd->fd_in = fd;
	}
	else if (current->type == HEREDOC)
	{
		/* TODO
			HEREDOC LOGIC
		*/
		// fd = ft_heredoc(current->file, NULL);
		if (fd == -1)
			return (handle_exec_err(current->file, errno), -1);
		cmd->fd_in = current->fd;
	}
	return (1);
}

int	open_fill_fds(t_tree *cmd)
{
	t_redir	*current;
	int			ret;

	ret = 1;
	current = cmd->redir;
	while (current)
	{
		if (is_infile(current))
			ret = handle_infile(cmd, current);
		else if (is_outfile(current))
			ret = handle_outfile(cmd, current);
		if (ret == -1)
			return (-1);
		current = current->next;
	}
	return (1);
}
