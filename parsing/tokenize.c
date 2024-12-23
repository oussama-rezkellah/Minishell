/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 23:47:53 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/23 02:28:02 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	add_quoted(char **tok, char **str, char quote)
{
	int		l;
	int		i;
	char	*to_join;

	l = len_quoted (*str, quote);
	if (l < 0)
		return (0);
	i = 0;
	to_join = ft_malloc (l + 1, MAL);
	while (l - i > 0)
		to_join[i++] = *((*str)++);
	to_join[i] = 0;
	*tok = ft_strjoin (*tok, to_join);
	return (1);
}

static void	add_unquoted(char **tok, char **str)
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

static char	*get_content(char **str)
{
	char	*to_ret;

	to_ret = ft_strdup("");
	while (**str && !ft_isspace(**str) && check_type(*str) == WORD)
	{
		if (**str == '"' || **str == '\'')
		{
			if (!add_quoted(&to_ret, str, **str))
				return (NULL);
		}
		else
			add_unquoted(&to_ret, str);
	}
	return (to_ret);
}

static t_lst_toks	*get_next_tok(char **str)
{
	t_tok	type;
	char	*content;

	content = NULL;
	type = get_type(str);
	if (type == WORD)
	{
		content = get_content(str);
		if (!content)
			return (NULL);
	}
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
		if (!new_node)
			return (NULL);
		add_tok_back(&lst_toks, new_node);
		while (ft_isspace(**str))
			(*str)++;
	}
	return (lst_toks);
}
