/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 08:50:20 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/24 19:00:36 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

long long	ft_atol(const char *str, int *err)
{
	unsigned long long	ret;
	int					sign;

	ret = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		ret = ret * 10 + *str - '0';
		if ((ret > LLONG_MAX && sign == 1)
			|| !ft_isdigit(*str))
			return ((*err = 1), -1);
		if (sign == -1 && (ret - 1) > LLONG_MAX)
			return ((*err = 1), -1);
		str++;
	}
	return ((int)ret * sign);
}

void p_exit(int pipe)
{
	if (!pipe)
		printf_fd(1, "exit\n");
}

int	valid_arg(char *arg, long long *exit_)
{
	int	err;

	if (!*arg)
		return (0);
	err = 0;
	*exit_ = ft_atol(arg, &err);
	if (err)
		return (0);
	return (1);
}

int	exit_cmd(char **argv, int exit_stat, int pipe)
{
	long long	exit_;
	const char	*err[] = {"too many arguments",
		"numeric argument required", NULL};
	if (!argv[0])
		return (ft_malloc(0, CLEAR), ft_malloc(0, CLEAR_ENV), \
		p_exit(pipe), exit(exit_stat), 1);
	if (valid_arg(argv[0], &exit_))
	{
		if (argv[1])
			return (p_exit(pipe), printf_fd(2, "minishell: exit: %s\n", \
			(char *)err[0]), ft_malloc(0, CLEAR), \
			exit_status(SET, 1), 1);
	}
	else
	{
		return (p_exit(pipe),printf_fd(2, "minishell: exit: %s: %s\n", \
			argv[0], (char *)err[1]), ft_malloc(0, CLEAR) \
		, ft_malloc(0, CLEAR_ENV), exit(255), 1);
	}
	return (p_exit(pipe), exit((int)exit_ & 255), (int)exit_ & 255);
}
