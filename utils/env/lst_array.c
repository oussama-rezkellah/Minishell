/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 23:45:32 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/24 22:05:19 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_name(char *env)
{
	char	*name;
	size_t	len;
	size_t	start;

	len = ft_strlen(env) - ft_strlen(ft_strchr(env, '='));
	name = ft_malloc(len + 1, MAL_ENV);
	start = -1;
	while (++start < len)
		name[start] = env[start];
	name[start] = 0;
	return (name);
}

static char	*get_value(char *env)
{
	char *value;

	value = ft_strchr(env, '=');
	// if (!value || ft_strlen(value) < 2)
	// 	return (NULL);
	return (ft_strdup_env (ft_strchr(env, '=') + 1));
}

void	array_to_lst(char **env, t_env **new_env)
{
	char	*value;
	char	*name;

	*new_env = NULL;
	while (*env)
	{
		name = get_name (*env);
		value = get_value (*env);
		if (!ft_strcmp(name, "PWD") && value)
			get_set_cwd(SET, value, NULL);
		lst_addback_env(new_env, create_env(name, value));
		env++;
	}
	shlvl(new_env);
	ft_malloc(1, CLEAR);
}

char	**lst_to_array(t_env *lst_env)
{
	size_t	len;
	size_t	start;
	char	**env;

	len = lstsize_env(lst_env);
	env = ft_malloc(sizeof(char *) * (len + 1), MAL);
	start = -1;
	while (++start < len)
	{
		env[start] = lst_env->env;
		lst_env = lst_env->next;
	}
	env[start] = NULL;
	return (env);
}
