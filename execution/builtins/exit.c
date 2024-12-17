/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 08:50:20 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/17 09:00:05 by aben-hss         ###   ########.fr       */
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

int	valid_arg(char *arg, long long *exit_)
{
	int	err;

	err = 0;
	*exit_ = ft_atol(arg, &err);
	if (err)
		return (0);
	return (1);
}

int	exit_cmd(char **argv, int exit_status)
{
	long long	exit_;

	if (!argv[0])
		return (ft_malloc(0, CLEAR), ft_malloc(0, CLEAR_ENV), exit(exit_status), 1);
	if (valid_arg(argv[0], &exit_))
	{
		if (argv[1])
			return (printf_fd(2, "exit\nexit: too many arguments\n"), \
			ft_malloc(0, CLEAR), ft_malloc(0, CLEAR_ENV), exit(exit_ & 255), 1);
	}
	else
	{
		return (printf_fd(2, "exit\nexit: %s: numeric argument required\n", argv[0]), \
		ft_malloc(0, CLEAR), ft_malloc(0, CLEAR_ENV), exit(255), 1);
	}
	return (0);
}

