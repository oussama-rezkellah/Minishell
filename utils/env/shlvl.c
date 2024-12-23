/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:19:09 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/22 21:40:42 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	shlvl(t_env **env)
{
	char	*string;

	string = env_get(*env, "SHLVL");
	if (!string || !*string || ft_atoi(string) > 999)
	{
		env_set(env, "SHLVL", "1");
		return ;
	}
	if (ft_atoi(string) == 999)
	{
		env_set(env, "SHLVL", "");
		return ;
	}
	if (ft_atoi(string) < 0)
	{
		env_set(env, "SHLVL", "0");
		return ;
	}
	env_set(env, "SHLVL", ft_itoa((ft_atoi(string)+1)));
}
