/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:19:20 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/23 13:44:13 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static size_t	count_args(char *s)
{
	size_t	count;
	int		in_s_q;
	int		in_d_q;
	int		i;

	count = 0;
	in_s_q = 0;
	in_d_q = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !in_d_q)
			in_s_q = !in_s_q;
		if (s[i] == '"' && !in_s_q)
			in_d_q = !in_d_q;
		if ((i == 0 && !ft_isspace(s[i])) || (ft_isspace(s[i]) && s[i+1] && \
		!ft_isspace(s[i+1]) && !in_d_q && !in_s_q))
			count++;
		i++;
	}
	return (count);
}

static int	alloc_element(char **element, char *s, int len)
{
	*element = ft_malloc(len + 1, MAL);
	ft_strlcpy(*element, s, len + 1);
	return (1);
}

char	**split_cmd(char *s)
{
	size_t	arg_count;
	char	**ret;
	size_t	i;
	size_t	j;
	int		in_s_q;
	int		in_d_q;

	i = 0;
	j = 0;
	arg_count = count_args(s);
	ret = ft_malloc(sizeof(char *) * (arg_count + 1), MAL);
	while (*s)
	{
		in_s_q = 0;
		in_d_q = 0;
		i = 0;
		while (ft_isspace(*s))
			s++;
		while (s[i] && (in_s_q || in_d_q || !ft_isspace(s[i])))
		{
			if (s[i] == '\'' && !in_d_q)
				in_s_q = !in_s_q;
			if (s[i] == '"' && !in_s_q)
				in_d_q = !in_d_q;
			if (!in_s_q && !in_d_q && ft_isspace(s[i]))
				break ;
			i++;
		}
		if (i > 0)
			alloc_element(&ret[j++], s, i);
		s += i;
	}
	ret[j] = NULL;
	return (ret);
}
