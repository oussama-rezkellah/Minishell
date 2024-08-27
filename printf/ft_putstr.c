/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 04:12:39 by orezkell          #+#    #+#             */
/*   Updated: 2024/08/25 23:37:02 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_putstr(int fd, char *str, int *ret)
{
	if (str == NULL)
	{
		ft_putstr(fd, "(null)", ret);
		return ;
	}
	while (*str)
	{
		ft_putchar(fd, *str, ret);
		str++;
	}
}
