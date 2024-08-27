/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 01:47:03 by orezkell          #+#    #+#             */
/*   Updated: 2024/08/26 01:47:21 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	char	occ;
	char	*res;

	res = (char *)s;
	occ = (char)c;
	while (*res)
	{
		if (*res == occ)
			return (res);
		res++;
	}
	if (occ == *res)
		return (res);
	return (NULL);
}
