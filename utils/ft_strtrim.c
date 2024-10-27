/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:30:52 by orezkell          #+#    #+#             */
/*   Updated: 2024/10/27 21:24:16 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	int	check_set(char const c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && check_set(s1[start], set))
		start++;
	while (end > start && check_set(s1[end], set))
		end--;
	ret = ft_malloc (end - start + 2, MAL);
	ft_strlcpy(ret, s1 + start, end - start + 2);
	return (ret);
}
