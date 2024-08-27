/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 23:45:32 by orezkell          #+#    #+#             */
/*   Updated: 2024/08/27 03:11:19 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char    *get_name (char *env)
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

char    *get_value (char *env)
{
    return (ft_strdup_env (ft_strchr(env, '=') + 1));
}

void	array_to_lst(char **env, t_env **new_env)
{
    char    *tmp;
    char    *value;
    char    *name;
    size_t  i;

	*new_env = NULL;
    while (*env)
    {
        name = get_name (*env);
        value = get_value (*env);
        lst_addback_env (new_env, lstnew_env(value, name, ft_strdup_env(*env)));
        env++;
    }
}

char	**lst_to_array(t_env *lst_env)
{
	size_t  len;
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
	env[++start] = NULL;
	return (env);
}