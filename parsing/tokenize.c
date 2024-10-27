/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 23:47:53 by orezkell          #+#    #+#             */
/*   Updated: 2024/10/28 00:00:45 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_quoted(char **tok, char **str, char quote)
{
	int		l;
	int		i;
	char	*to_join;

	l = len_quoted (*str, quote);
	i = 0;
	to_join = ft_malloc (l + 1, MAL);
	while (l - i > 0)
		to_join[i++] = *((*str)++);
	to_join[i] = 0;
	*tok = ft_strjoin (*tok, to_join);
}

void	add_unquoted(char **tok, char **str)
{
	int		l;
	int		i;
	char	*to_join;

	l = len_unquoted (*str);
	i = 0;
	to_join = ft_malloc (l + 1, MAL);
	while (l - i > 0)
	{
		to_join[i++] = **str;
		(*str)++;
	}
	to_join[i] = 0;
	*tok = ft_strjoin (*tok, to_join);
}

char	*get_content(char **str)
{
	char	*to_ret;

	to_ret = ft_strdup("");
	while (**str && !ft_isspace(**str) && check_type(*str) == NOT)
	{
		if (**str == '"' || **str == '\'')
			add_quoted(&to_ret, str, **str);
		else
			add_unquoted(&to_ret, str);
	}
	return (to_ret);
}

t_lst_toks	*get_next_tok(char **str)
{
	tok		type;
	char	*content;

	content = NULL;
	type = get_type(str);
	if (type == NOT)
		content = get_content(str);
	return (ft_toknew (content, type));
}

t_lst_toks	*tokenize(char **str)
{
	t_lst_toks	*new_node;
	t_lst_toks	*lst_toks;

	lst_toks = NULL;
	while (**str)
	{
		new_node = get_next_tok(str);
		add_tok_back(&lst_toks, new_node);
		while (ft_isspace(**str))
			(*str)++;
	}
	return (lst_toks);
}
