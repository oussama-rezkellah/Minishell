/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:22:12 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/23 01:59:30 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*found_in_list(t_env *env, char *name);

char	*get_full_var(char *name, char *value)
{
	char	*full_var;
	size_t	len;

	len = ft_strlen(name) + 2;
	if (value)
		len += ft_strlen(value);
	full_var = ft_malloc(len, MAL_ENV);
	if (!full_var)
		return (NULL);
	full_var = ft_strcpy(full_var, name);
	full_var = ft_strcat(full_var, "=");
	if (value)
		full_var = ft_strcat(full_var, value);
	return (full_var);
}

void	set_or_append_env(char *name, char *value, t_mode mode, t_env **env)
{
	t_env	*existing;
	t_env	*new_entry;
	char	*full_var;

	existing = found_in_list(*env, name);
	if (existing)
	{
		if (mode == APPEND_MODE && existing->value)
			existing->value = ft_strjoin_env(existing->value, value);
		else if (mode == SET_MODE && existing->value && value)
		{
			existing->value = ft_strdup_env(value);
		}
		existing->env = get_full_var(name, existing->value);
	}
	else
	{
		if (value)
			value = ft_strdup_env(value);
		full_var = get_full_var(name, value);
		new_entry = lstnew_env(ft_strdup_env(name), value, full_var);
		lst_addback_env(env, new_entry);
	}
}

void	display_environment(t_env *env)
{
	while (env)
	{
		printf_fd(1, "declare -x %s", env->name);
		if (env->value)
			printf_fd(1, "=\"%s\"", env->value);
		printf_fd(1, "\n");
		env = env->next;
	}
}

int	export_(char *input, t_env **env)
{
	char	*name;
	char	*value;
	char	*equals_pos;

	equals_pos = ft_strchr(input, '=');
	if (equals_pos && ft_strlen(input) > 1)
	{
		name = ft_strndup(input, equals_pos - input);
		value = equals_pos + 1;
		if (name[ft_strlen(name) - 1] == '+')
		{
			name[ft_strlen(name) - 1] = '\0';
			if (is_valid_name(name))
			{
				set_or_append_env(name, value, APPEND_MODE, env);
				return (0);
			}
		}
		else if (is_valid_name(name))
			return (set_or_append_env(name, value, SET_MODE, env), 0);
	}
	else if (is_valid_name(input))
		return (set_or_append_env(input, NULL, SET_MODE, env), 0);
	return (printf_fd(2, "minishell: export: `%s': not a valid identifier\n", input), 1);
}

int	export_cmd(char **argv, t_env **env)
{
	int	i;
	int	ret;

	ret = 0;
	if ((!argv || !*argv) && env)
		return (display_environment(*env), 1);
	i = 0;
	while (argv[i])
	{
		if (export_(argv[i], env))
			ret = 1;
		i++;
	}
	return (ret);
}
