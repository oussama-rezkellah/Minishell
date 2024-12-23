/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:08:46 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/23 14:38:55 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	is_directory(const char *path)
{
	struct stat	path_stat;

	if (!path)
		return ;
	if (stat(path, &path_stat) != 0)
		return ;
	if (S_ISDIR(path_stat.st_mode) \
		&& (path[ft_strlen(path) - 1] == '/' || (path[0] == '/') || \
		(path[0] == '.' && path[1] == '/')))
	{
		printf_fd(2, "minishell: %s: is a directory\n", path);
		exit_status(SET, 126);
		exit(126);
	}
}

void	execute_external(char **argv, t_env *envp)
{
	char	*path;
	char	**env;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	env = lst_to_array(envp);
	is_directory(argv[0]);
	path = find_command_path(argv[0], env);
	if (!ft_strcmp(path, "\200"))
		exit(127) ;
	if (!path && errno != EACCES)
	{
		handle_exec_err(argv[0], -127);
		exit(127);
	}
	execve(path, argv, env);
	if (argv && argv[0] && !argv[0][0])
		errno = -127;
	exit(handle_exec_err(argv[0], errno));
}

static void	handle_child_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			printf_fd(1, "\n");
		else if (WTERMSIG(status) == SIGQUIT)
			printf_fd(1, "Quit: 3\n");
		status = (128 + WTERMSIG(status));
	}
	else
		status = WEXITSTATUS(status);
	exit_status(SET, status);
}

static void	execute_command(char **cmd, t_env *env)
{
	int	pid;
	int	status;

	signal(SIGINT, SIG_IGN);
	pid = ft_fork(env);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		execute_external(cmd, env);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	handle_child_status(status);
}

void	cmd_exec(t_tree *node, t_env **env)
{
	char	**cmd;

	if (!node || !node->p_cmd)
		return ;
	cmd = ft_expand(node, *env);
	if (!cmd)
		return ;
	if (!cmd[0])
		return ((void)exit_status(SET, 0));
	node->fd_in = 0;
	node->fd_out = 1;
	if (open_fill_fds(node) == -1 || handle_redirections(node) == -1)
		return ((void)exit_status(SET, 1));
	if (is_builtin(cmd[0]))
		return ((void)exit_status(SET, execute_builtin(cmd, *env)));
	execute_command(cmd, *env);
}
