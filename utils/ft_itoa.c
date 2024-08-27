/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 05:24:53 by orezkell          #+#    #+#             */
/*   Updated: 2024/08/27 05:27:51 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	size_t	int_len(long n)
{
	size_t	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	tmp;
	char	*s;
	size_t	start;
	size_t	len;

	tmp = n;
	len = int_len(n);
	start = 0;
	if (n < 0 || !len)
		len++;
	s = (char *)ft_malloc (len + 1, MAL);
	if (!s)
		return (NULL);
	if (n < 0)
	{
		tmp *= -1;
		s[start++] = '-';
	}
	s[len] = 0;
	while (len-- > start)
	{
		s[len] = (tmp % 10) + '0';
		tmp /= 10;
	}
	return (s);
}
