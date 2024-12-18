/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 00:17:25 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/18 21:04:10 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

char* handle_quote(char* result, char q, int *in_q, int* other_q)
{
	char temp_char[2] = {q, '\0'};
	
	if (!*other_q)
		*in_q = !*in_q;
	return ft_strjoin(result, temp_char);
}

int extract_var_name(char** input, char** var_name)
{
	int j = 0;
	int i = -1;
	while (ft_isalnum(*(*input + j)) || *(*input + j) == '_')
		j++;
	*var_name = ft_malloc(j + 1, MAL);
	while (++i < j)
		(*var_name)[i] = (*input)[i];
	(*var_name)[i] = 0;
	return j;
}

char* handle_var(char *ret, char** input, t_env *env)
{
	char	*tmp;
	char	*var_name;
	char	*var_value;

	tmp = ft_strdup (" ");
	var_name = NULL;
	var_value = NULL;
	(*input)++;
	if (**input == '?')
		return (*input)++,ft_strjoin(ret, ft_itoa(exit_status(GET,0)));
	if(ft_isalpha(**input) || **input == '_')
	{
		(*input) = (*input) + extract_var_name(input, &var_name);
		var_value = env_get(env ,var_name);
		if (var_value)
			return ft_strjoin(ret, var_value);
		return ret;
	}
	tmp[0] = '$';
	return ft_strjoin(ret, tmp);
}

char* process_char(char *ret, char** input, int* s_q,int* d_q, t_env *env)
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
	return (*input)++,ft_strjoin(ret, tmp);
}

char *replace_values(char **str, t_env *env)
{
	char *to_ret = ft_strdup("");
	int s_q = 0;
	int d_q = 0;

	while (**str)
		to_ret = process_char(to_ret, str, &s_q, &d_q, env);
	return (to_ret);
}

size_t count_args(char *s)
{
	size_t count = 0;
	int in_s_q = 0;
	int in_d_q = 0;
	int i = 0;

	while (s[i])
	{
		if (s[i] == '\'' && !in_d_q)
			in_s_q = !in_s_q;
		if (s[i] == '"' && !in_s_q)
			in_d_q = !in_d_q;
		if (in_s_q || in_d_q)
		{
			i++;
			continue;
		}
		if ((i == 0 && s[i] != ' ') || (s[i] == ' ' && s[i+1] && s[i+1] != ' '))
			count++;
		i++;
	}
	return count;
}

char **alloc_array(char **str, int n)
{
	str = ft_malloc(sizeof(char *) * (n + 1), MAL);
	return (str);
}

int alloc_element(char **element, char *s, int len)
{
	*element = ft_malloc(len + 1, MAL);

	ft_strlcpy(*element, s, len + 1);
	return 1;
}

char **split_cmd(char *s)
{
	size_t arg_count;
	char **ret;
	size_t i = 0;
	size_t j = 0;
	int in_s_q;
	int in_d_q;

	arg_count = count_args(s);
	ret = ft_malloc(sizeof(char *) * (arg_count + 1), MAL);
	while (*s)
	{
		in_s_q = 0;
		in_d_q = 0;
		i = 0;
		while (*s == ' ')
            s++;
		while (s[i] && (in_s_q || in_d_q || s[i] != ' '))
		{
			if (s[i] == '\'' && !in_d_q)
				in_s_q = !in_s_q;
			if (s[i] == '"' && !in_s_q)
				in_d_q = !in_d_q;
			if (!in_s_q && !in_d_q && s[i] == ' ')
                break;
			i++;
		}
		if (i > 0)
			alloc_element(&ret[j++], s, i);
		s += i;
	}
	ret[j] = NULL;
	return ret;
}

int	main(int ac, char **av, char **env)
{
	t_minishell	sh;
	char		*input;

	(void)ac;
	(void)av;
	(void)env;
	initialise_env (&sh.env, env);
	// t_env *tmp = sh.env;
	// while (tmp)
	// {
	// 	printf_fd (1, "%s:", tmp->name);
	// 	printf_fd (1, "%s\n", tmp->value);
	// 	// printf_fd (1, "%s \n", tmp->env);
	// 	tmp = tmp->next;
	// }
	char *test = ft_strdup("$\"USER    \"$$$ 'te  st'ou ss");
	char **test1 = split_cmd (replace_values(&test, sh.env));
	while (*test1)
	{
		printf("%s\n", *test1);
		test1++;
	}
	exit(0);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		add_history(input);
		if (!parsing(&sh, input))
		{
			ft_malloc (0, CLEAR);
			continue ;
		}
		ft_malloc (0, CLEAR);
	}
	ft_malloc (0, CLEAR_ENV);
}

	// TEST for ENV