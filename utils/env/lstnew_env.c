/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 02:12:11 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/22 21:39:42 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*create_env(char *name, char *value)
{
	char	*tmp_name;
	char	*tmp_value;
	char	*tmp_env;

	tmp_name = ft_strdup_env(name);
	tmp_value = ft_strdup_env(value);
	tmp_env = tmp_name;
	if (tmp_value)
		tmp_env = ft_strdup_env(ft_strjoin(ft_strjoin(tmp_env, "="), \
			tmp_value));
	return (lstnew_env(tmp_name, tmp_value, tmp_env));
}

t_env	*lstnew_env(char *name, char *value, char *env)
{
	t_env	*new;

	new = (t_env *)ft_malloc (sizeof(t_env), MAL_ENV);
	new->value = value;
	new->name = name;
	new->env = env;
	new->next = NULL;
	return (new);
}
