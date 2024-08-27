/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstsize_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 03:14:59 by orezkell          #+#    #+#             */
/*   Updated: 2024/08/26 03:17:18 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t    lstsize_env(t_env *lst_env)
{
	size_t	i;

	i = 0;
	while (lst_env)
	{
		i++;
		lst_env = lst_env->next;
	}
	return (i);
}