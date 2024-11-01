/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_addback_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 02:08:29 by orezkell          #+#    #+#             */
/*   Updated: 2024/11/01 03:13:07 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	lst_addback_env(t_env **new_env, t_env *new)
{
	t_env	*tmp;

	if (!new || !new_env)
		return ;
	if (!(*new_env))
	{
		*new_env = new;
		return ;
	}
	tmp = *new_env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
}
