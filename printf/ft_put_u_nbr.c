/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_u_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 04:21:38 by orezkell          #+#    #+#             */
/*   Updated: 2024/08/25 23:36:59 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_put_u_nbr(int fd, unsigned int n, int *ret)
{
	if (n < 10)
	{
		ft_putchar(fd, n + '0', ret);
	}
	else
	{
		ft_putnbr(fd, n / 10, ret);
		ft_putnbr(fd, n % 10, ret);
	}
}
