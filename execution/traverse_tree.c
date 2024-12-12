/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:19:20 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/11 23:00:48 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	or_exec(t_tree *node, t_env **env)
{
	execution (node->l_child, env);
	if (exit_status(GET, 0))
		return (execution(node->r_child, env));
}

void	and_exec(t_tree *node, t_env **env)
{
	execution (node->l_child, env);
	if (!exit_status(GET, 0))
		return (execution(node->r_child, env));
}

void	execution (t_tree *node, t_env **env)
{
	if (!node)
		return ;
	if (node->type == OR)
		return (or_exec(node, env));
	if (node->type == AND)
		return (and_exec(node, env));
	if (node->type == PIPE)
		return (pipe_exec(node, env));
	if (node->type == CMD)
		return (cmd_exec(node, env));
}
