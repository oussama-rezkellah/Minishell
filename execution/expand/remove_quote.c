/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:19:09 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/23 13:34:07 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*process_char(char *to_ret, char *str, int i, int *s_q, int *d_q)
{
	char	*tmp;

	tmp = ft_strdup(" ");
	if (str[i] == '\'' && !*d_q)
	{
		*s_q = !*s_q;
		return (to_ret);
	}
	if (str[i] == '"' && !*s_q)
	{
		*d_q = !*d_q;
		return (to_ret);
	}
	if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\'') && \
	!*s_q && !*d_q)
		return (to_ret);
	tmp[0] = str[i];
	return (ft_strjoin(to_ret, tmp));
}

char	*remove_q_line(char *str)
{
	char	*to_ret;
	int		s_q;
	int		d_q;
	size_t	i;

	to_ret = ft_strdup("");
	s_q = 0;
	d_q = 0;
	i = -1;
	while (str[++i])
		to_ret = process_char(to_ret, str, i, &s_q, &d_q);
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
