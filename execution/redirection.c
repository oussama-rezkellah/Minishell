/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:05:33 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/23 21:53:19 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		if (current ->fd == -1)
			return (handle_exec_err("heredoc", errno), -1);
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		cmd->fd_in = dup(current->fd);
		close(current->fd);
	}
	return (1);
}

int	open_fill_fds(t_tree *cmd)
{
	t_redir	*current;
	int		ret;

	ret = 1;
	current = cmd->redir;
	if (!current)
		return (1);
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
	return (handle_redirections(cmd));
}
