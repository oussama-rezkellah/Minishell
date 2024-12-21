/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:27:51 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/21 06:35:18 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_env_args(char **cmd)
{
	int ret;

	ret = 1;
	if (!access(cmd[1], F_OK))
		errno = EACCES;
	else
		errno = ENOENT;
	ret = handle_exec_err(cmd[1], errno);
	return (ret);
}

int	env_cmd(t_env *env, char **cmd)
{
	int ret;

	ret = 0;
	if (!env)
		return (1);
	if (cmd[1])
	{
		ret  = handle_env_args(cmd);
		return ret;
	}
	while (env)
	{
		if (env->name && env->value)
			printf_fd(1, "%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (ret);
}
