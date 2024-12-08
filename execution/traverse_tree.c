/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_tree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aferd <aferd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:19:20 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/07 21:52:33 by aferd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	or_exec(t_tree *node, t_env **env)
{
	execution (node->l_child, env);
	if (exit_status(GET, 0))
		return (execution(node->l_child, env));
}

void	and_exec(t_tree *node, t_env **env)
{
	execution (node->l_child, env);
	if (!exit_status(GET, 0))
		return (execution(node->l_child, env));
}

char	*single_q_fill(char *ret, char *s, int *i)
{
	while (s[*i])
	{
		ret = join_char(ret, s[(*i)++]);
		if (s[*i] == '\'')
		{
			ret = join_char(ret, s[(*i)++]);
			return (ret);
		}
	}
	return (ret);
}

int	ft_isalpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	is_1valid(char c)
{
	return (ft_isalpha(c) || c == '_' || c == '?');
}

int	ft_isnum(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_valid_env(char c)
{
	return (is_1valid(c) || ft_isnum(c));
}

char	*get_env_value(char *val, t_env *env)
{
	while(env)
	{
		if(!ft_strncmp(val, env->name, ft_strlen(val)))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

char	*expand_var(char *ret, int *i, char *s, t_env *env)
{
	char	*env_var;
	int		env_size;

	(*i)++;
	env_size = *i;
	if (s[env_size] == '?')
		return ((*i)++,
			ft_strjoin(ret, ft_itoa(exit_status(GET, 0))));
	while (is_valid_env(s[env_size]))
		env_size++;
	env_size -= *i;
	env_var = ft_substr(s, *i, env_size);
	env_var = get_env_value(env_var, env);
	*i += env_size;
	if (!env_var)
		return (ret);
	ret = ft_strjoin(ret, env_var);
	return (ret);
}

char	*double_q_fill(char *ret, char *s, int *i, t_env **env)
{
	ret = join_char(ret, s[(*i)++]);
	while (s[*i])
	{
		if (s[*i] == '$' && is_1valid(s[(*i) + 1]))
			ret = expand_var(ret, i, s, *env);
		else if (s[*i] == '"')
		{
			ret = join_char(ret, s[(*i)++]);
			break ;
		}
		else
			ret = join_char(ret, s[(*i)++]);
	}
	return (ret);
}

char	*switch_in_single_q(char *str)
{
	int		i;
	char	*new;

	new = ft_malloc(sizeof(char) * (ft_strlen(str) + 1), MAL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			new[i] = str[i];
			while (str[++i] != '\'')
			{
				if (str[i] == ' ')
					new[i] = -1;
				else if (str[i] == '\t')
					new[i] = -2;
				else if (str[i] == '"')
					new[i] = -3;
				else
					new[i] = str[i];
			}
		}
		new[i] = str[i];
	}
	new[i] = '\0';
	return (new);
}

char	*switch_in_double_q(char *str)
{
	char	*new;
	int		i;

	new = ft_malloc(sizeof(char) * (ft_strlen(str) + 1), MAL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			new[i] = str[i];
			while (str[++i] != '"')
			{
				if (str[i] == ' ')
					new[i] = -1;
				else if (str[i] == '\t')
					new[i] = -2;
				else
					new[i] = str[i];
			}
		}
		new[i] = str[i];
	}
	new[i] = '\0';
	return (new);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	c;
	char	new[4000];

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"'
			|| str[i] == '\'')
		{
			c = str[i++];
			while (str[i] != c)
				new[j++] = str[i++];
			i++;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
	return (ft_strdup(new));
}

char	*switch_back(char *str)
{
	int		i;
	char	*new;

	new = ft_malloc(sizeof(char) * (ft_strlen(str) + 1), MAL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == -1)
			new[i] = ' ';
		else if (str[i] == -2)
			new[i] = '\t';
		else if (str[i] == -3)
			new[i] = '"';
		else
			new[i] = str[i];
	}
	new[i] = '\0';
	return (remove_quotes(new));
}

void	format_and_split(char *result, t_tree *node)
{
	int		i;
	char	**new;

	i = 0;
	result = switch_in_single_q(result);
	result = switch_in_double_q(result);
	new = ft_split(result, " \t");
	while (new[i])
	{
		new[i] = switch_back(new[i]);
		i++;
	}
	node->cmd = new;
}

void	expand_cmd(t_tree *node, t_env **env)
{
	int		i;
	char	*result;
	char	*n;

	result = ft_strdup("");
	n = node->p_cmd;
	i = 0;
	while (n[i])
	{
		if (n[i] == '\'')
			result = single_q_fill(result, n, &i);
		else if (n[i] == '"')
			result = double_q_fill(result, n, &i, env);
		else if (n[i] == '$' && is_1valid(n[i + 1]))
			result = expand_var(result, &i, n, *env);
		else if (n[i] == '$' && (n[i + 1] == '"' || n[i + 1] == '\''))
			i++;
		else
			result = join_char(result, n[i++]);
	}
	format_and_split(result, node);
}

void	cmd_exec(t_tree *node, t_env **env)
{
	expand_cmd(node, env);
}

void	execution(t_tree *node, t_env **env)
{
	if (!node)
		return ;
	if (node->type == OR)
		return (or_exec(node, env));
	if (node->type == AND)
		return (and_exec(node, env));
	if (node->type == CMD)
		return (cmd_exec(node, env));
}
