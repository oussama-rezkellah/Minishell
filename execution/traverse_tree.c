/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:19:20 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/13 16:50:56 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_builtin(char *cmd)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env",
		"exit", NULL};
	int			i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd, (char *)builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	execute_builtin(char **cmd, t_env *env)
{
	if (ft_strcmp(cmd[0], "export") == 0)
		return (export_cmd(cmd + 1, &env));
	return (1);
}

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
