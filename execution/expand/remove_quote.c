/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:19:09 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/23 17:21:15 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*process_char(char *to_ret, char *str, int i, t_quote *q)
{
	char	*tmp;

	tmp = ft_strdup(" ");
	if (str[i] == '\'' && !q->d_q)
	{
		q->s_q = !q->s_q;
		return (to_ret);
	}
	if (str[i] == '"' && !q->s_q)
	{
		q->d_q = !q->d_q;
		return (to_ret);
	}
	if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\'') && \
	!q->s_q && !q->d_q)
		return (to_ret);
	tmp[0] = str[i];
	return (ft_strjoin(to_ret, tmp));
}

char	*remove_q_line(char *str)
{
	char	*to_ret;
	size_t	i;
	t_quote	*q;

	to_ret = ft_strdup("");
	q = ft_malloc(sizeof(t_quote), MAL);
	q->s_q = 0;
	q->d_q = 0;
	i = -1;
	while (str[++i])
		to_ret = process_char(to_ret, str, i, q);
	return (to_ret);
}

char	**remove_q_cmd(char **cmd)
{
	char	**tmp;
	size_t	i;

	i = -1;
	tmp = cmd;
	while (tmp[++i])
		tmp[i] = remove_q_line(tmp[i]);
	return (tmp);
}
