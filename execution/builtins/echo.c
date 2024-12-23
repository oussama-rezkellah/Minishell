/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:27:14 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/23 03:46:16 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	flag_check(char *str)
{
	int	j;

	j = 0;
	if (!str || !*str)
		return (-1);
	if (str[j] == '-')
		j++;
	if (!str[j])
		return (0);
	while (str[j] == 'n')
		j++;
	if (str[j] == '\0')
		return (1);
	return (0);
}

static void	print_args(char **arg)
{
	printf_fd(1, "%s", arg[0]);
	if (arg[1])
		printf_fd(1, " ");
}

int	echo_cmd(char **arg)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if (!arg)
		return (0);
	i = 1;
	if (!arg[i] || !arg[i][0])
		return (printf_fd(1, "\n"), 0);
	while (flag_check(arg[i]))
	{
		flag = 1;
		if (flag == 1 && (!arg[i] || !arg[i][0]))
			return (0);
		i++;
	}
	while (arg[i])
	{
		print_args(&arg[i]);
		i++;
	}
	if (!flag)
		printf_fd(1, "\n");
	return (0);
}
