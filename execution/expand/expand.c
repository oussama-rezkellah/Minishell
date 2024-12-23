/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:19:09 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/23 08:58:05 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	expand_redir(t_tree *node, t_env *env)
{
	t_redir	*redir;
	char	**tmp;

	redir = node->redir;
	while (redir)
	{
		if (redir->type != HEREDOC)
		{
			redir->file = replace_values(&redir->file, env);
			tmp = split_cmd (redir->file);
			if (!tmp[0] || !tmp[0][0] || tmp[1])
				return (exit_status(SET, handle_exec_err(tmp[0], -77)), \
				0);
			redir->file = remove_q_line(tmp[0]);
		}
		redir = redir->next;
	}
	return (1);
}

char	**ft_expand(t_tree *node, t_env *env)
{
	char	**cmd;

	if (!node->p_cmd)
		return (NULL);
	node->p_cmd = replace_values(&node->p_cmd, env);
	cmd = split_cmd (node->p_cmd);
	if (!expand_redir(node, env))
		return (NULL);
	return (remove_q_cmd(cmd));
}
