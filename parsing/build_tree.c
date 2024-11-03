/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:19:09 by orezkell          #+#    #+#             */
/*   Updated: 2024/11/03 14:20:58 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_tree	*build_list(t_lst_toks *tokens)
{
	t_lst_toks	*tmp;
	t_tree		*tree;
	char		*cmd;
	t_redir		*redir;

	tmp = tokens;
	cmd = ft_strdup("");
	redir = NULL;
	tree = NULL;
	while (tmp)
	{
		if (tmp->type == 1 || (tmp->type >= 6 && tmp->type <= 9))
		{
			if (ft_strlen(cmd) || redir)
			{
				add_node_back(&tree, ft_nodenew(cmd, redir, CMD));
				cmd = ft_strdup("");
				redir = NULL;
			}
			add_node_back(&tree, ft_nodenew(NULL, NULL, tmp->type));
		}
		else if (tmp->type == WORD)
		{
			if (ft_strlen(cmd))
				cmd = ft_strjoin(cmd, " ");
			cmd = ft_strjoin(cmd, tmp->content);
		}
		else if (tmp->type >= 2 && tmp->type <= 5)
		{
			add_redir_back (&redir, ft_redirnew(tmp->next->content, tmp->type));
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	if (ft_strlen(cmd) || redir)
		add_node_back(&tree, ft_nodenew(cmd, redir, CMD));
	return (tree);
}

t_tree	*shunting_yard(t_tree	*tree)
{
	t_tree	*new;
	t_tree	*op;

	new = NULL;
	op = NULL;
	while (tree)
	{
		if (tree->type == CMD)
			push_back (&new, tree);
		else if (tree->type != RPR && tree->type != LPR)
		{
			while (op && get_pre(tree->type) <= get_pre(op->type))
				push_back_pop (&new, &op);
			push (&op, tree);
		}
		else if (tree->type == LPR)
			push (&op, tree);
		else if (tree->type == RPR)
			while (op->type != LPR || pop(&op))
				push_back_pop (&new, &op);
		tree = tree->r_child;
	}
	while (op)
		push_back_pop (&new, &op);
	return (new);
}

t_tree	*post_to_tree(t_tree *tree)
{
	t_stack	*stack;
	t_tree	*new;

	stack = NULL;
	new = NULL;
	while (tree)
	{
		if (tree->type == CMD)
			push_s (&stack, tree);
		else
		{
			new = ft_nodenew(tree->p_cmd, tree->redir, tree->type);
			new->r_child = pop_s(&stack);
			new->l_child = pop_s(&stack);
			push_s(&stack, new);
		}
		tree = tree->r_child;
	}
	return (pop_s(&stack));
}

void	build_tree(t_minishell *sh)
{
	sh->tree = NULL;
	sh->tree = build_list (sh->tokens);
	sh->tree = shunting_yard(sh->tree);
	sh->tree = post_to_tree (sh->tree);
}
