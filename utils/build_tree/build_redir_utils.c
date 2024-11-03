/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:45:35 by orezkell          #+#    #+#             */
/*   Updated: 2024/11/03 15:02:52 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_redir	*ft_redirnew(void *content, t_tok type)
{
	t_redir	*new;

	new = (t_redir *)ft_malloc (sizeof(t_redir), MAL);
	new->type = type;
	new->file = content;
	new->next = NULL;
	return (new);
}

void	add_redir_back(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	if (!new || !lst)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
}
