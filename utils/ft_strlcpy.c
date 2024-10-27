/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:43:06 by orezkell          #+#    #+#             */
/*   Updated: 2024/10/26 20:01:57 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (src[i])
		i++;
	if (dstsize < 1)
		return (i);
	j = 0;
	while (src[j] && j < dstsize - 1)
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = 0;
	return (i);
}
