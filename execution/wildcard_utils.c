#include "../inc/minishell.h"

int	is_hidden(char first, char *entry)
{
	if (first == '.' && entry[0] == '.')
		return (1);
	return (!(first != '.' && entry[0] == '.'));
}

int	pattern_match(char *entry, char *pattern)
{
	while (*entry && *pattern)
	{
		if (*pattern == '*')
			return (suffix_match(entry, pattern + 1));
		if (*pattern != *entry)
			return (0);
		entry++;
		pattern++;
	}
	return ((*pattern == '\0' || *pattern == '*')
		&& *entry == '\0');
}

int	suffix_match(char *entry, char *pattern)
{
	if (*pattern == '\0')
		return (1);
	while (*entry)
	{
		if (pattern_match(entry, pattern))
			return (1);
		entry++;
	}
	return (0);
}
