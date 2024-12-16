/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:29:04 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/04 11:03:19 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	go_home(t_env *env)
{
	char	*home;
    char    *old;

	home = env_get_var(env, "HOME");
    old = ft_strdup(home);
	if (!home)
	{
		printf_fd(2, "cd: HOME not set\n");
		return (0);
	}
    get_set_cwd(GET, NULL, old);
	if (chdir(home) == -1)
	{
		perror(home);
		return (0);
	}
    env_set_var(&env, "OLDPWD", ft_strdup_env(old));
    env_set_var(&env, "PWD", ft_strdup_env(home));
    get_set_cwd(SET, home, NULL);
	return (1);
}

void    handle_cd_failure(char *new, char *old, t_env *env)
{
    new = ft_strjoin(ft_strdup("/"), new);
    get_set_cwd(GET, NULL, old);
    new = ft_strjoin(old, new); 
    env_set_var(&env, "OLDPWD", ft_strdup_env(old));
    env_set_var(&env, "PWD", ft_strdup_env(new));
    get_set_cwd(SET, new, NULL);
    handle_exec_err(NULL, -69);
}

int	cd_cmd(t_env *env, char **argv)
{
	char	*old;
	char	*new;
    int     change;

    old = NULL;
    new = NULL;
	if (!argv[1] || !ft_strcmp(argv[1], "~"))
		return (go_home(env));
    if (argv[2])
    {
        return (printf_fd(2, "cd: too many arguments\n"), 1);
    }
    new = ft_strdup(argv[1]);
    change = chdir(new);
    if (change == 0)
    {
        old = ft_strdup(new);
	    get_set_cwd(GET, NULL, old);
	    env_set_var(&env, "OLDPWD", ft_strdup_env(old));
	    env_set_var(&env, "PWD", ft_strdup_env(new));
        get_set_cwd(SET, new, NULL);
        return (1);
    }
	else if (change == -1)
    {
        errno = ENOENT;
        if (!ft_strcmp(argv[1], ".") || !ft_strcmp(argv[1], ".."))
            handle_cd_failure(new, old, env);
        else
            handle_exec_err(ft_strjoin("cd: ", argv[1]), errno);
        return (1);
    }
	return (0);
}