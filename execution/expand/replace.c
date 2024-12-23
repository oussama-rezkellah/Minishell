/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:19:09 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/23 13:36:13 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*handle_quote(char	*result, char q, int *in_q, int *other_q)
{
	char	temp_char[2] = {q, '\0'};

	if (!*other_q)
		*in_q = !*in_q;
	return (ft_strjoin(result, temp_char));
}

static int	extract_var_name(char **input, char **var_name)
{
	int	j;
	int	i;

	j = 0;
	i = -1;
	while (ft_isalnum(*(*input + j)) || *(*input + j) == '_')
		j++;
	*var_name = ft_malloc(j + 1, MAL);
	while (++i < j)
		(*var_name)[i] = (*input)[i];
	(*var_name)[i] = 0;
	return (j);
}

static char	*handle_var(char *ret, char **input, t_env *env)
{
	char	*tmp;
	char	*var_name;
	char	*var_value;

	tmp = ft_strdup (" ");
	var_name = NULL;
	var_value = NULL;
	(*input)++;
	if (**input == '?')
		return ((*input)++, ft_strjoin(ret, ft_itoa(exit_status(GET, 0))));
	if (ft_isalpha(**input) || **input == '_')
	{
		(*input) = (*input) + extract_var_name(input, &var_name);
		var_value = env_get(env, var_name);
		if (var_value)
			return (ft_strjoin(ret, var_value));
		return (ret);
	}
	tmp[0] = '$';
	return (ft_strjoin(ret, tmp));
}

static char	*process_char(char *ret, char **input, int *s_q, int *d_q, t_env *env)
{
	char	*tmp;

	tmp = ft_strdup(" ");
	if (**input == '"' && !*s_q)
		return ((*input)++, handle_quote(ret, '"', d_q, s_q));
	if (**input == '\'' && !*d_q)
		return ((*input)++, handle_quote(ret, '\'', s_q, d_q));
	if (**input == '$' && !*s_q)
		return (handle_var(ret, input, env));
	tmp[0] = **input;
	return ((*input)++, ft_strjoin(ret, tmp));
}

char	*replace_values(char **str, t_env *env)
{
	char	*to_ret;
	int		s_q;
	int		d_q;

	to_ret = ft_strdup("");
	s_q = 0;
	d_q = 0;
	while (**str)
		to_ret = process_char(to_ret, str, &s_q, &d_q, env);
	return (to_ret);
}
