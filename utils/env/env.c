/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 03:17:13 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/17 00:03:43 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#include "../../inc/minishell.h"

char    *env_get_var(t_env *env , char *name)
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

void	env_set_var(t_env **env , char *name, char *value)
{
	t_env *tmp;
	char *env_tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(name , tmp->name))
		{
			tmp->value = ft_strdup_env(value);
			tmp->env = ft_strjoin(name , "=");
			tmp->env = ft_strdup_env (ft_strjoin(tmp->env, value));
			return ;
		}
		tmp = tmp->next;
	}
	env_tmp = ft_strjoin(name , "=");
	env_tmp = ft_strjoin(env_tmp , value);
	lst_addback_env(env, lstnew_env(ft_strdup_env(name) , ft_strdup_env(value), ft_strdup_env(env_tmp)));
	return ;
}

void	init_empty(t_env **new_env)
{
	char	*pwd;

	*new_env = NULL;
	lst_addback_env(new_env, create_env("PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		lst_addback_env(new_env, create_env("PWD", pwd));
		free(pwd);
	}
	get_set_cwd(SET, ft_strdup(pwd), NULL);
	lst_addback_env(new_env, create_env("SHLVL", "1"));
	lst_addback_env(new_env, create_env("OLDPWD", NULL));
	ft_malloc(1, CLEAR);
}

void	initialise_env(t_env **new_env, char **env)
{
	if (!env || !(*env))
		init_empty (new_env);
	else
		array_to_lst (env, new_env);
}
