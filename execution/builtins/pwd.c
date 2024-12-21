/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:41:00 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/21 06:13:21 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_set_cwd(t_exit mode, char *new_cwd, char **old_cwd)
{
	static char	*cwd;
	char		*tmp;

	if (!cwd)
	{
		tmp = getcwd(NULL, 0);
		cwd = ft_strdup_env(tmp);
		free(tmp);
	}
	if (mode == SET)
	{
		cwd = ft_strdup_env(new_cwd);
		return ;
	}
	else if (mode == GET)
	{
		*old_cwd = ft_strdup(cwd);
		return ;
	}
}

int	pwd_cmd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		get_set_cwd(GET, NULL, &cwd);
		if (!cwd)
			return (perror("getcwd"), 1);
	}
	printf_fd(1, "%s\n", cwd);
	return (free(cwd), 0);
}
