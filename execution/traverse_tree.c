/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aferd <aferd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:19:20 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/07 21:52:33 by aferd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	or_exec(t_tree *node, t_env **env)
{
	execution (node->l_child, env);
	if (exit_status(GET, 0))
		return (execution(node->l_child, env));
}

void	and_exec(t_tree *node, t_env **env)
{
	execution (node->l_child, env);
	if (!exit_status(GET, 0))
		return (execution(node->l_child, env));
}

void	cmd_exec(t_tree *node, t_env **env)
{
	expand_cmd(node, env);
}

void	execution(t_tree *node, t_env **env)
{
	if (!node)
		return ;
	if (node->type == OR)
		return (or_exec(node, env));
	if (node->type == AND)
		return (and_exec(node, env));
	if (node->type == CMD)
		return (cmd_exec(node, env));
}
