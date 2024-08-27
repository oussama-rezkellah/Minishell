/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 04:15:44 by orezkell          #+#    #+#             */
/*   Updated: 2024/08/25 23:37:02 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_putnbr(int fd, int n, int *ret)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar(fd, '-', ret);
		nb *= -1;
	}
	if (nb < 10)
	{
		ft_putchar(fd, nb + '0', ret);
	}
	else
	{
		ft_putnbr(fd, nb / 10, ret);
		ft_putnbr(fd, nb % 10, ret);
	}
}
