/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 03:17:13 by orezkell          #+#    #+#             */
/*   Updated: 2024/08/27 03:12:12 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_empty(t_env **new_env)
{
	char	*pwd;

	*new_env = NULL;
	pwd = NULL;
	lst_addback_env(new_env, lstnew_env(ft_strdup_env("1"), ft_strdup_env("SHLVL"), ft_strdup_env("SHLVL=1")));
	pwd = getcwd(pwd, sizeof(pwd));
	if (pwd)
	{
		lst_addback_env(new_env, lstnew_env(ft_strdup_env(pwd), ft_strdup_env("PWD"), ft_strdup_env(ft_strjoin("PWD=", pwd))));
		free(pwd);
	}
}

void	initialise_env (t_env **new_env, char **env)
{
	if (!env || !(*env))
		init_empty (new_env);
	else
		array_to_lst (env, new_env);
}