/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shunting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:08:35 by orezkell          #+#    #+#             */
/*   Updated: 2024/11/03 15:03:09 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	push(t_tree **stack, t_tree *to_push)
{
	t_tree	*new;

	new = ft_nodenew(to_push->p_cmd, to_push->redir, to_push->type);
	new->r_child = (*stack);
	*stack = new;
}

void	push_back(t_tree **stack, t_tree *to_push)
{
	add_node_back(stack, ft_nodenew(to_push->p_cmd, to_push->redir, \
	to_push->type));
}

int	pop(t_tree **stack)
{
	(*stack) = (*stack)->r_child;
	return (0);
}

void	push_back_pop(t_tree **stack, t_tree **to_push)
{
	add_node_back(stack, ft_nodenew((*to_push)->p_cmd, (*to_push)->redir, \
	(*to_push)->type));
	pop (to_push);
}

int	get_pre(t_tok op)
{
	if (op == PIPE)
		return (2);
	else if (op == OR || op == AND)
		return (1);
	else if (op == CMD)
		return (3);
	return (0);
}
