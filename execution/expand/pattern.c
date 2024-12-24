/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 17:34:05 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/23 17:34:07 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_quotes(char **pattern, int *in_s_q, int *in_d_q)
{
	if (**pattern == '\'' && !(*in_d_q))
	{
		*in_s_q = !(*in_s_q);
		(*pattern)++;
		return (1);
	}
	if (**pattern == '"' && !(*in_s_q))
	{
		*in_d_q = !(*in_d_q);
		(*pattern)++;
		return (1);
	}
	return (0);
}

static int	handle_wildcard(char **pattern, char **str, int in_s_q, int in_d_q)
{
	if (**pattern == '*' && !in_s_q && !in_d_q)
	{
		while (*(*pattern + 1) == '*')
			(*pattern)++;
		if (*(*pattern + 1) == '\0')
			return (1);
		while (**str != '\0')
		{
			if (match_pattern(*pattern + 1, *str))
				return (1);
			(*str)++;
		}
		return (0);
	}
	return (-1);
}

static int	handle_escape(char **pattern, char **str)
{
	if (**pattern == '\\')
	{
		(*pattern)++;
		if (**pattern == '\0' || **pattern != **str)
			return (0);
	}
	return (1);
}

int	match_pattern(char *pattern, char *str)
{
	int	in_s_q;
	int	in_d_q;
	int	wildcard_result;

	in_s_q = 0;
	in_d_q = 0;
	while (*pattern != '\0')
	{
		if (handle_quotes(&pattern, &in_s_q, &in_d_q))
			continue ;
		wildcard_result = handle_wildcard(&pattern, &str, in_s_q, in_d_q);
		if (wildcard_result != -1)
			return (wildcard_result);
		if (!handle_escape(&pattern, &str))
			return (0);
		if (*pattern != *str)
			return (0);
		pattern++;
		str++;
	}
	if (*str)
		return (0);
	return (1);
}
