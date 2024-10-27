/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 23:46:46 by orezkell          #+#    #+#             */
/*   Updated: 2024/10/27 23:47:32 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_lst_toks	*ft_toknew(void *content, tok type)
{
	t_lst_toks	*new;

	new = (t_lst_toks *)ft_malloc (sizeof(t_lst_toks), MAL);
	if (!new)
		return (NULL);
	new->content = content;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	add_tok_back(t_lst_toks **lst, t_lst_toks *new)
{
	t_lst_toks	*tmp;

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