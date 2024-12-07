/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:37:09 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/07 13:05:09 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char    *env_get(t_env *env , char *name)
{
	t_env *tmp;
	
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(name , tmp->name, ft_strlen (name)) \
		&& ft_strlen (name) == ft_strlen (tmp->name))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

void	env_set(t_env **env , char *name, char *value)
{
	t_env *tmp;
	char *env_tmp;
	
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(name , tmp->name, ft_strlen (name)) \
		&& ft_strlen (name) == ft_strlen (tmp->name))
		{
			tmp->value = ft_strdup_env(value);
			tmp->env = ft_strjoin(name , ":");
			tmp->env = ft_strdup_env (ft_strjoin(tmp->env, value));
			return ;
		}
		tmp = tmp->next;
	}
	env_tmp = ft_strjoin(name , ":");
	env_tmp = ft_strjoin(env_tmp , value);
	lst_addback_env(env, lstnew_env(ft_strdup_env(name) , ft_strdup_env(value), ft_strdup_env(env_tmp)));
	return ;
}