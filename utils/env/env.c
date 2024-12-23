/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 03:17:13 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/22 21:35:33 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_empty(t_env **new_env)
{
	char	*pwd;

	*new_env = NULL;
	lst_addback_env(new_env, create_env("PATH", \
		"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
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
