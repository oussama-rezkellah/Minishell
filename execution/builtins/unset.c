/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:07:26 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/23 12:00:06 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*found_in_list(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	is_valid_name(char *name)
{
	if (!name || !*name || !(ft_isalpha(*name) || *name == '_'))
		return (0);
	while (*name)
	{
		if (!(ft_isalnum(*name) || *name == '_'))
			return (0);
		name++;
	}
	return (1);
}

int	env_unset(t_env **env_list, const char *name)
{
	t_env	*current;
	t_env	*prev;

	if (!name || !*name)
		return (-1);
	prev = NULL;
	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->name, (char *)name) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (-1);
}

int	unset_cmd(t_env **env, char **argv)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (!argv)
		return (ret);
	while (argv[i])
	{
		if (is_valid_name(argv[i]))
			env_unset(env, argv[i]);
		else
		{
			printf_fd(2, "minishell: unset: `%s': not a valid identifier\n", \
			argv[i]);
			ret = 1;
		}
		i++;
	}
	return (ret);
}
