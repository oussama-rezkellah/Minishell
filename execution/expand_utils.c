#include "../inc/minishell.h"

int	is_valid_env(char c)
{
	return (is_1valid(c) || ft_isnum(c));
}

char	*get_env_value(char *val, t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(val, env->name, ft_strlen(val)))
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
