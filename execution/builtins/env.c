/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:27:51 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/17 09:28:01 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	env_cmd(t_env *env)
{
	if (!env)
		return (1);
	while (env)
	{
		if (env->name && env->value)
			printf_fd(1, "%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}
