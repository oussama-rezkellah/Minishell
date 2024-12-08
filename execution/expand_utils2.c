#include "../inc/minishell.h"

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

char	**remove_all_quotes(char **old)
{
	int	i;

	i = 0;
	while (old[i])
	{
		if (old[i])
			old[i] = remove_quotes(old[i]);
		i++;
	}
	return (old);
}
