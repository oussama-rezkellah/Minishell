#include "../inc/minishell.h"

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
	return (new[i] = 0, new);
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
	return (new);
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
	node->cmd = remove_all_quotes(expand_wildcard(new));
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
