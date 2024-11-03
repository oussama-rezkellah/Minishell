/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:31:31 by orezkell          #+#    #+#             */
/*   Updated: 2024/11/03 15:02:48 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree	*ft_nodenew(void *content, t_redir	*redir, t_tok type)
{
	t_tree	*new;

	new = (t_tree *)ft_malloc (sizeof(t_tree), MAL);
	new->type = type;
	new->p_cmd = content;
	new->redir = redir;
	new->r_child = NULL;
	new->l_child = NULL;
	return (new);
}

void	add_node_back(t_tree **lst, t_tree *new)
{
	t_tree	*tmp;

	if (!new || !lst)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->r_child)
		tmp = tmp->r_child;
	tmp->r_child = new;
	new->r_child = NULL;
}
