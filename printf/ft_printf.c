/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 03:55:38 by orezkell          #+#    #+#             */
/*   Updated: 2024/08/25 23:36:58 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static void	check_flags(int fd, va_list args, char str, int *ret)
{
	if (str == 'd' || str == 'i')
		ft_putnbr(fd, va_arg(args, int), ret);
	else if (str == 'u')
		ft_put_u_nbr(fd, va_arg(args, unsigned int), ret);
	else if (str == 'c')
		ft_putchar(fd, (char)va_arg(args, int), ret);
	else if (str == 's')
		ft_putstr(fd, va_arg(args, char *), ret);
	else if (str == 'x')
		ft_putnbr_base(fd, va_arg(args, unsigned int), str, ret);
	else if (str == 'X')
		ft_putnbr_base(fd, va_arg(args, unsigned int), str, ret);
	else if (str == 'p')
		ft_putadress(fd, va_arg(args, void *), ret);
	else
		ft_putchar(fd, str, ret);
}

int	printf_fd(int fd, const char *str, ...)
{
	va_list	args;
	int		ret;

	ret = 0;
	if (write(fd, "", 0) == -1)
		return (-1);
	va_start (args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			check_flags (fd, args, *str, &ret);
		}
		else
			ft_putchar (fd, *str, &ret);
		if (*str)
			str++;
	}
	va_end (args);
	return (ret);
}
