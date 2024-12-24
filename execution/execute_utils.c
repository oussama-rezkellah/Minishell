/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 05:29:29 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/24 14:42:20 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_exec_err(char *cmd, int errno_val)
{
	printf_fd(2, "minishell: ");
	printf_fd(2, cmd);
	printf_fd(2, ": ");
	if (errno_val == -69)
		return (printf_fd(2, "cd: error retrieving current directory: \
		getcwd: cannot access parent directories: No such file or \
		directory\n"), exit_status(SET, 1));
	if (errno_val == -127)
		return (printf_fd(2, "command not found\n"), 127);
	if (errno_val == -77)
		return (printf_fd(2, "ambiguous redirect\n"), 1);
	else if (errno_val == EACCES)
		return (printf_fd(2, "Permission denied\n"), \
			exit_status(SET, 126), 126);
	else if (errno_val == ENOENT)
		return (printf_fd(2, "No such file or directory\n"), \
			exit_status(SET, 127), 127);
	else
		return (printf_fd(2, "%s\n", strerror(errno_val)), \
			exit_status(SET, 1), 1);
}

char	**get_paths(char **env)
{
	char	*path;
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	while (env[i])
	{
		if (!strncmp(env[i], "PATH", 4))
		{
			if (ft_strlen(env[i]) == 5)
				break ;
			path = ft_strdup((strchr(env[i], '=')) + 1);
			paths = ft_split(path, ':');
			return (paths);
		}
		i++;
	}
	paths = ft_malloc(2 * sizeof(char *), MAL);
	paths[0] = ft_strdup("\200\0");
	paths[1] = NULL;
	return (paths);
}

bool	is_a_directory(const char *path)
{
	struct stat	path_stat;

	if (!path)
		return (false);
	if (stat(path, &path_stat) != 0)
		return (false);
	return (S_ISDIR(path_stat.st_mode)
		&& (path[ft_strlen(path) - 1] == '/' || (path[0] == '/') || \
			(path[0] == '.' && path[1] == '/')));
}

static char	*check_direct_path(char *cmd)
{
	if (cmd && (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/')))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		handle_exec_err(cmd, errno);
		exit(exit_status(GET, 0));
		return (NULL);
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **env)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (!env)
		return (NULL);
	full_path = check_direct_path(cmd);
	if (full_path)
		return (full_path);
	paths = get_paths(env);
	if (!ft_strcmp(paths[0], "\200"))
	{
		if (access(ft_strjoin("./", cmd), X_OK) == 0)
			return (ft_strdup(cmd));
		return (handle_exec_err(cmd, ENOENT), ft_strdup("\200\0"));
	}
	i = -1;
	while (paths[++i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		if (access(full_path, F_OK) == 0 && !is_a_directory(full_path))
			return (full_path);
	}
	return (NULL);
}
