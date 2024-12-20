/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:08:46 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/20 02:41:06 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	if (cmd && (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/')))
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

	if (!node || !node->p_cmd || !*(node->p_cmd))
		return ;
	// cmd = expand command
	stat = 0;
	pid = -1;
	cmd = ft_expand(node , *env);
	node->fd_in = 0;
	node->fd_out = 1;
	if (open_fill_fds(node) == -1)
		return ;
	if (is_builtin(cmd[0]))
		return ((void)execute_builtin(cmd, *env));
	if (handle_redirections(node) == -1)
		return ;
	// if ((*env)->pipe_flag == 0)
	// {
		pid = fork();
		if (pid == 0)
		{
			execute_external(cmd, *env);
			exit(EXIT_FAILURE);
		}
	// }
	// else if ((*env)->pipe_flag == 1)
	// {
	// 	(*env)->pipe_flag = 0;
	// 	execute_external(cmd, *env);
	// }
	exit_status(SET, ft_wait(pid, pid, &stat));
}
