/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 03:17:13 by orezkell          #+#    #+#             */
/*   Updated: 2024/11/01 03:13:07 by orezkell         ###   ########.fr       */
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
	pwd = NULL;
	lst_addback_env(new_env, lstnew_env(\
	ft_strdup_env("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."), \
	ft_strdup_env("PATH"), \
	ft_strdup_env("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.")));
	pwd = getcwd(pwd, sizeof(pwd));
	get_set_cwd(SET, ft_strdup(pwd), NULL);
	if (pwd)
	{
		lst_addback_env(new_env, lstnew_env(ft_strdup_env(pwd), \
		ft_strdup_env("PWD"), ft_strdup_env(ft_strjoin("PWD=", pwd))));
		free(pwd);
	}
	lst_addback_env(new_env, lstnew_env(ft_strdup_env("1"), \
	ft_strdup_env("SHLVL"), ft_strdup_env("SHLVL=1")));
	lst_addback_env(new_env, lstnew_env(NULL, ft_strdup_env("OLDPWD"), \
	ft_strdup_env("OLDPWD=")));
	ft_malloc(1, CLEAR);
}

void	initialise_env(t_env **new_env, char **env)
{
	if (!env || !(*env))
		init_empty (new_env);
	else
		array_to_lst (env, new_env);
}
