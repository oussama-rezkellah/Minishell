/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 04:23:59 by orezkell          #+#    #+#             */
/*   Updated: 2024/08/25 23:37:01 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_putnbr_base(int fd, unsigned int nbr, char c, int *ret)
{
	unsigned int	base_len;
	char			*base;

	base_len = 16;
	if (c == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (nbr < base_len)
	{
		ft_putchar(fd, base[nbr % base_len], ret);
	}
	else
	{
		ft_putnbr_base(fd, nbr / base_len, c, ret);
		ft_putnbr_base(fd, nbr % base_len, c, ret);
	}
}
