#include "../inc/minishell.h"

int	entry_count(char *pattern)
{
	struct dirent	*entry;
	int				count;
	DIR				*current;

	current = opendir(".");
	if (!current)
		return (-1);
	count = 0;
	entry = readdir(current);
	while (entry)
	{
		if (pattern_match(entry->d_name, pattern))
			if (is_hidden(pattern[0], entry->d_name))
				count++;
		entry = readdir(current);
	}
	closedir(current);
	return (count);
}

int	new_args_count(char **args)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '*'))
			count += entry_count(args[i]);
		else
			count++;
		i++;
	}
	return (count);
}

void	expand_arg(char **new, int *args_i, char *pattern)
{
	struct dirent	*entry;
	DIR				*current;

	current = opendir(".");
	if (!current)
		return ;
	entry = readdir(current);
	while (entry)
	{
		if (pattern_match(entry->d_name, pattern))
		{
			if (is_hidden(pattern[0], entry->d_name))
				new[(*args_i)++] = ft_strdup(entry->d_name);
		}
		entry = readdir(current);
	}
	closedir(current);
}

char	**expand_wildcard(char **old)
{
	char	**new;
	int		args_size;
	int		args_i;
	int		i;

	args_size = new_args_count(old);
	if (!args_size)
		return (old);
	i = -1;
	args_i = 0;
	new = ft_malloc(sizeof(char *) * (args_size + 2), MAL);
	while (old[++i])
	{
		if (!ft_strchr(old[i], '*')
			|| old[i][0] == '\'' || old[i][0] == '"'
			|| !entry_count(old[i]))
			new[args_i++] = ft_strdup(old[i]);
		else
			expand_arg(new, &args_i, old[i]);
	}
	new[args_i] = NULL;
	return (new);
}
