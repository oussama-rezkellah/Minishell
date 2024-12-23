/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:37:09 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/22 21:37:23 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*env_get(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			if (!tmp->value)
				return (NULL);
			return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	env_set(t_env **env, char *name, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
		{
			tmp->value = ft_strdup_env(value);
			tmp->env = ft_strjoin(name, "=");
			tmp->env = ft_strdup_env (ft_strjoin(tmp->env, value));
			return ;
		}
		tmp = tmp->next;
	}
	lst_addback_env(env, create_env(name, value));
	return ;
}
