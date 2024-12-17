/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:29:04 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/17 08:48:52 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	go_home(t_env *env)
{
	char	*home;
	char	*cwd;

	home = env_get(env, "HOME");
	cwd = ft_strdup(home);
	if (!home)
	{
		printf_fd(2, "cd: HOME not set\n");
		return (0);
	}
	get_set_cwd(GET, NULL, &cwd);
	if (chdir(home) == -1)
	{
		perror(home);
		return (0);
	}
	env_set(&env, "OLDPWD", cwd);
	env_set(&env, "PWD", home);
	get_set_cwd(SET, home, NULL);
	return (1);
}

void	handle_cd_failure(char *new, char *current_wd, t_env *env)
{
	char *joined;

	get_set_cwd(GET, NULL, &current_wd);
	env_set(&env, "OLDPWD", current_wd);
	if (current_wd[ft_strlen(current_wd) - 1] != '/')
		current_wd = ft_strjoin_env(current_wd, "/");
	joined = ft_strjoin_env(current_wd, new);
	env_set(&env, "PWD", joined);
	get_set_cwd(SET, joined, NULL);
	handle_exec_err(NULL, -69);
}

int	cd_cmd(t_env *env, char **argv)
{
	char	*cwd;
	char	*new;
	char	*flag;
	int		change;

	if (!argv[1] || !ft_strcmp(argv[1], "~"))
		return (go_home(env));
	if (argv[2])
		return (printf_fd(2, "cd: too many arguments\n"), 1);
	new = ft_strdup(argv[1]);
	change = chdir(new);
	get_set_cwd(GET, NULL, &cwd);
	flag = getcwd(NULL, 0);
	if (flag && change == 0)
		return (env_set(&env, "OLDPWD", cwd),env_set(&env, "PWD", flag), \
				get_set_cwd(SET, flag, NULL), free(flag), 0);
	else if (!flag || change == -1)
	{
		if ((!ft_strcmp(new, ".") || !ft_strcmp(new, "..")) && !change)
			return (handle_cd_failure(new, cwd, env), 1);
		else if (change == -1)
			return (handle_exec_err(ft_strjoin("cd: ", argv[1]), errno), free(flag), 1);
	}
	return (free(flag), 0);
}
