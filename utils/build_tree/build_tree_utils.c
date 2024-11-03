/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:07:32 by orezkell          #+#    #+#             */
/*   Updated: 2024/11/03 15:03:00 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_stack	*ft_nodestack_new(void *content, t_redir *redir, t_tok type)
{
	t_stack	*new;

	new = (t_stack *)ft_malloc (sizeof(t_stack), MAL);
	new->node = ft_nodenew(content, redir, type);
	new->next = NULL;
	return (new);
}

void	push_s(t_stack	**stack, t_tree *to_push)
{
	t_stack	*new;

	new = ft_nodestack_new(to_push->p_cmd, to_push->redir, to_push->type);
	if (to_push->type != CMD)
	{
		new->node->r_child = to_push->r_child;
		new->node->l_child = to_push->l_child;
	}
	new->next = (*stack);
	*stack = new;
}

t_tree	*pop_s(t_stack **stack)
{
	t_tree	*to_ret;

	to_ret = ft_nodenew((*stack)->node->p_cmd, (*stack)->node->redir, \
	(*stack)->node->type);
	if ((*stack)->node->type != CMD)
	{
		to_ret->r_child = (*stack)->node->r_child;
		to_ret->l_child = (*stack)->node->l_child;
	}
	(*stack) = (*stack)->next;
	return (to_ret);
}
