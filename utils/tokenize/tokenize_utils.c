/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 23:44:28 by orezkell          #+#    #+#             */
/*   Updated: 2024/10/27 23:45:21 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

tok	get_type (char **str)
{
	if (**str == '|' && *(*str + 1) == '|')
		return *str = *str + 2,OR;
	else if (**str == '&' && *(*str + 1) == '&')
		return *str = *str + 2,AND;
	else if (**str == '<' && *(*str + 1) == '<')
		return *str = *str + 2,HEREDOC;
	else if (**str == '>' && *(*str + 1) == '>')
		return *str = *str + 2,APPEND;
	else if (**str == '|')
		return (*str)++, PIPE;
	else if (**str == '<')
		return (*str)++,IN;
	else if (**str == '>')
		return (*str)++,OUT;
	else if (**str == '(')
		return (*str)++,LPR;
	else if (**str == ')')
		return (*str)++,RPR;
	else 
		return NOT;
}

tok	check_type (char *str)
{
	if (*str == '|' && (*str + 1) == '|')
		return OR;
	else if (*str == '&' && (*str + 1) == '&')
		return AND;
	else if ( *str == '<' && (*str + 1) == '<')
		return HEREDOC;
	else if (*str == '>' && (*str + 1) == '>')
		return APPEND;
	else if (*str == '|')
		return PIPE;
	else if (*str == '<')
		return IN;
	else if (*str == '>')
		return OUT;
	else if (*str == '(')
		return LPR;
	else if (*str == ')')
		return RPR;
	else 
		return NOT;
}

int	len_quoted (char *str, char quote)
{
	int i = 1;
	while (str[i] != quote && str[i] )
		i++;
	if (!*str)
		return (printf ("error \n"), -1);
	i++;
	return i;
}

int	len_unquoted (char *str)
{
	int i = 0;
	while (str[i] && !ft_isspace (str[i]) && str[i] != '"' && str[i] != '\'' && check_type(str + i) == NOT)
		i++;
	return i;
}