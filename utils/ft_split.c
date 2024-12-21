#include "../inc/minishell.h"

static char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dst[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dst[i] = '\0';
		++i;
	}
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*sub_str;
	char	*empty_str;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (len == 0 || start >= s_len)
	{
		empty_str = (char *)ft_malloc(1, MAL);
		if (!empty_str)
			return (NULL);
		if (empty_str)
			empty_str[0] = '\0';
		return (empty_str);
	}
	if (len > s_len - start)
		len = s_len - start;
	sub_str = (char *)ft_malloc(len + 1, MAL);
	if (!sub_str)
		return (NULL);
	ft_strncpy(sub_str, s + start, len);
	sub_str[len] = '\0';
	return (sub_str);
}

static size_t	substr_counter(char const *s, char c)
{
	size_t		num_of_substrs;
	char const	*ptr;

	ptr = s;
	num_of_substrs = 0;
	while (*ptr)
	{
		while (*ptr == c && *ptr)
			ptr++;
		if (*ptr)
			num_of_substrs++;
		while (*ptr != c && *ptr)
			ptr++;
	}
	return (num_of_substrs);
}

static char	*alloc(const char *str, char c, int *i)
{
	char	*ret;
	size_t	size;

	ret = NULL;
	size = 0;
	while (str [*i] == c && str[*i])
		*i += 1;
	while (str[size + *i] != c && str[size + *i])
		size++;
	ret = ft_substr(str, *i, size);
	if (!ret)
		return (NULL);
	*i += size;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		n;
	int		sub_count;
	int		i;

	i = 0;
	n = 0;
	if (!s)
		return (NULL);
	sub_count = substr_counter(s, c);
	ret = (char **)ft_malloc(sizeof(char *) * (sub_count + 1), MAL);
	if (!ret)
		return (NULL);
	while (n < sub_count && *s)
	{
		ret[n] = alloc(s, c, &i);
		if (!ret[n])
		{
			return (NULL);
		}
		n++;
	}
	ret[n] = NULL;
	return (ret);
}