/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:58:33 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/13 00:02:58 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

void traverse_cmd_nodes(t_tree *node,t_env *env, void (*open_heredoc)(t_tree *, t_env *))
{
	if (node == NULL)
		return;
	if (node->type == CMD)
	{
		if (open_heredoc != NULL)
			open_heredoc(node, env);
	}
	traverse_cmd_nodes(node->l_child, env, open_heredoc);
	traverse_cmd_nodes(node->r_child, env, open_heredoc);
}

void open_heredoc(t_tree *cmd, t_env *env)
{
	t_redir	*current;

	if (!cmd->redir)
		return ;
	current = cmd->redir;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			current->fd = ft_heredoc(current->file, env);
			if (current ->fd == -1)
			{
				handle_exec_err("heredoc", errno);
				return ;
			}
		}
		current = current->next;
	}
	return ;
}


int open_all_heredocs(t_minishell *sh)
{
	traverse_cmd_nodes(sh->tree, sh->env, open_heredoc);
	return (1);
}