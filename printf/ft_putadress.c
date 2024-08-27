/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 04:38:14 by orezkell          #+#    #+#             */
/*   Updated: 2024/08/25 23:36:59 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_putbase(int fd, unsigned long int ptr, int *ret)
{
	char	*base;

	base = "0123456789abcdef";
	if (ptr < 16)
	{
		ft_putchar(fd, base[ptr % 16], ret);
	}
	else
	{
		ft_putbase(fd, ptr / 16, ret);
		ft_putbase(fd, ptr % 16, ret);
	}
}

void	ft_putadress(int fd, void *p, int *ret)
{
	unsigned long int	ptr;

	ptr = (unsigned long int)p;
	ft_putstr(fd, "0x", ret);
	ft_putbase(fd, ptr, ret);
}
