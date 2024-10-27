/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 02:03:04 by orezkell          #+#    #+#             */
/*   Updated: 2024/10/28 00:07:00 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		i;

	p = ft_malloc (ft_strlen (s1) + 1, MAL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = 0;
	return (p);
}
