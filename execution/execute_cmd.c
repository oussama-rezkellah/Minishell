/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:08:46 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/18 03:38:05 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	**get_paths(char **env)
{
	char	*path;
	char	**paths;
	int		i;

	i = 0;
	while (env[i])
	{
		if (!strncmp(env[i], "PATH", 4))
		{
			path = ft_strdup((strchr(env[i], '=')) + 1);
			paths = ft_split(path, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **env)
{
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	if (!env)
		return (NULL);
	paths = get_paths(env);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
	}
	return (NULL);
}

void	execute_external(char **argv, t_env *envp)
{
	char	*path;
	char	**env;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	env = lst_to_array(envp);
	path = find_command_path(argv[0], env);
	if (!path)
	{
		handle_exec_err(argv[0], -127);
		exit(127);
	}
	execve(path, argv, env);
	if (argv && argv[0] && !argv[0][0])
		errno = -127;
	handle_exec_err(NULL, errno);
	exit(126);
}
int	handle_redirections(t_tree *node);

void	cmd_exec(t_tree *node, t_env **env)
{
	char	**cmd;
	int		stat;
	int		pid;

	if (!node)
		return ;
	// cmd = expand command
	stat = 0;
	pid = -1;
	cmd = ft_split(node->p_cmd, ' ');
	node->fd_in = 0;
	node->fd_out = 1;
	if (open_fill_fds(node) == -1)
		return ;
	if (is_builtin(cmd[0]))
		return ((void)execute_builtin(cmd, *env));
	if (handle_redirections(node) == -1)
		return ;
	if ((*env)->pipe_flag == 0)
	{
		pid = fork();
		if (pid == 0)
			execute_external(cmd, *env);
	}
	else if ((*env)->pipe_flag == 1)
	{
		(*env)->pipe_flag = 0;
		execute_external(cmd, *env);
	}
	exit_status(SET, ft_wait(pid, pid, &stat));
}
