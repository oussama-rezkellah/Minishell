/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:08:46 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/24 17:40:40 by aben-hss         ###   ########.fr       */
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

static void	execute_command(char **cmd, t_env *env, t_data *data)
{
	int	pid;
	int	status;

	if (!cmd[0])
		return ;
	signal(SIGINT, SIG_IGN);
	pid = ft_fork(env, data);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		execute_external(cmd, env);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	handle_child_status(status);
}

void	cmd_exec(t_tree *node, t_env **env, t_data *data)
{
	char	**cmd;

	if (!node)
		return ;
	node->fd_in = 0;
	node->fd_out = 1;
	cmd = ft_expand(node, *env);
	if (!cmd && !node->redir)
		return ;
	if (open_fill_fds(node) == -1)
		return (clean_heredoc(node), (void)exit_status(SET, 1));
	if (is_builtin(cmd[0]))
		return ((void)exit_status(SET, execute_builtin(cmd, env, node->pipe)));
	if (!cmd[0])
		return ((void)exit_status(SET, 0));
	execute_command(cmd, *env, data);
}
