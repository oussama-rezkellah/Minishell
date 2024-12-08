/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aferd <aferd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:32:41 by aferd             #+#    #+#             */
/*   Updated: 2024/12/07 20:01:02 by aferd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*hold;
	size_t	str_len;
	size_t	size;
	size_t	index;

	if (!s)
		return (NULL);
	index = 0;
	str_len = ft_strlen(s);
	if (start >= str_len)
		size = 0;
	else if (str_len - start < len)
		size = (str_len - start);
	else
		size = len;
	hold = (char *)ft_malloc(sizeof(char) * (size + 1), MAL);
	while (index < size)
	{
		hold[index] = s[start + index];
		index++;
	}
	hold[index] = '\0';
	return (hold);
}
