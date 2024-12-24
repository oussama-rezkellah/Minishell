/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:29:41 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/24 09:35:13 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_quote(int *in_q, int *other_q)
{
	if (!*other_q)
		*in_q = !*in_q;
}

int	is_hidden(char first, char *entry)
{
	if (first == '.' && entry[0] == '.')
		return (1);
	return (!(first != '.' && entry[0] == '.'));
}

char	*expand_arg(char *pattern)
{
	struct dirent	*entry;
	DIR				*current;
	char			*to_ret;

	to_ret = ft_strdup("");
	current = opendir(".");
	if (!current)
		return (pattern);
	entry = readdir(current);
	while (entry)
	{
		if (match_pattern(pattern, entry->d_name))
		{
			if (is_hidden(pattern[0], entry->d_name))
				to_ret = ft_strjoin (to_ret, ft_strjoin(" ", entry->d_name));
		}
		entry = readdir(current);
	}
	closedir(current);
	if (*to_ret)
		return (to_ret);
	return (pattern);
}

void join_char(char *tmp, char **buffer,char **input)
{
	tmp[0] = **input;
	*buffer = ft_strjoin(*buffer, tmp);
	(*input)++;
}

static char	*process_char(char *ret, char **input, int *s_q, int *d_q)
{
	char	*tmp;
	char	*buffer;
	int		flg;

	flg = 0;
	tmp = ft_strdup(" ");
	buffer = ft_strdup("");
	while (ft_isspace(**input))
		(*input)++;
	while (**input && !ft_isspace(**input))
	{
		if (**input == '"' && !*s_q)
			handle_quote(d_q, s_q);
		if (**input == '\'' && !*d_q)
			handle_quote(s_q, d_q);
		if (**input == '*' && !*s_q && !*d_q)
			flg = 1;
		join_char(tmp, &buffer, input);
		while (ft_isspace(**input) && (*s_q || *d_q))
			join_char(tmp, &buffer, input);
	}
	if (flg)
		buffer = expand_arg(buffer);
	return (ft_strjoin(ret, ft_strjoin(" ", buffer)));
}

char	*ft_wildcard(char **s)
{
	char	*to_ret;
	int		s_q;
	int		d_q;

	to_ret = ft_strdup("");
	d_q = 0;
	s_q = 0;
	while (**s)
		to_ret = process_char(to_ret, s, &s_q, &d_q);
	return (to_ret);
}
