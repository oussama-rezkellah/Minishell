/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 12:27:26 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/07 13:08:22 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void cd_home (t_env **env)
{
	char *cwd;
	char *home;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		//error
	home = env_get(*env, "HOME");
	if (!home)
	{
		free(cwd);
		//error
	}
	if (chdir(home))
	{
		free(cwd);
		//error
	}
	env_set(env, "PWD", home);
	env_set(env, "OLDPWD", cwd);
	free(cwd);
}

void    ft_cd(char **cmd , t_env **env)
{
	if (!cmd[1] || !ft_strncmp (cmd[1], "~", 2))
		return (cd_home(env)); 
	
}