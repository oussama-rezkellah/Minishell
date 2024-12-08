/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aferd <aferd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 04:23:32 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/07 19:41:53 by aferd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*new_str;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = (char *)ft_malloc (len, MAL);
	if (!new_str)
		return (NULL);
	ret = new_str;
	while (*s1)
		*new_str++ = *s1++;
	while (*s2)
		*new_str++ = *s2++;
	*new_str = 0;
	return (ret);
}

char	*join_char(char *s1, char c)
{
	char	*s2;

	s2 = ft_malloc(sizeof(char) * 2, MAL);
	s2[0] = c;
	s2[1] = '\0';
	return (ft_strjoin(s1, s2));
}
