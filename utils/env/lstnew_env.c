/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 02:12:11 by orezkell          #+#    #+#             */
/*   Updated: 2024/11/01 03:13:07 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*lstnew_env(char *value, char *name, char *env)
{
	t_env	*new;

	new = (t_env *)ft_malloc (sizeof(t_env), MAL_ENV);
	new->value = value;
	new->name = name;
	new->env = env;
	new->next = NULL;
	return (new);
}
