/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:08:46 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/21 06:46:56 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_command_path(char *cmd, char **env);
char	**get_paths(char **env);

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
	exit(handle_exec_err(NULL, errno));
}
int	handle_redirections(t_tree *node);

void	cmd_exec(t_tree *node, t_env **env)
{
	char	**cmd;
	int		status;
	int		pid;

	if (!node || !node->p_cmd || !*(node->p_cmd))
		return ;
	// cmd = expand command
	status = 0;
	pid = -1;
	cmd = ft_expand(node , *env);
	node->fd_in = 0;
	node->fd_out = 1;
	if (open_fill_fds(node) == -1 && handle_redirections(node) == -1)
		return ;
	if (is_builtin(cmd[0]))
		return ((void)execute_builtin(cmd, *env));
	pid = fork();
	if (pid < 0)
	{
		handle_exec_err("fork: ", errno);
		exit(1);
	}
	if (pid == 0)
	{
			// signal(SIGINT, handle_sigint);
			// signal(SIGQUIT, SIG_IGN);
			execute_external(cmd, *env);
			exit(EXIT_FAILURE);
	}

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			printf_fd(1, "\n");
		else if (WTERMSIG(status) == SIGQUIT)
			printf_fd(1, "Quit: 3\n");
		status = (128 + WTERMSIG(status));
	}
	else
		status =  (WEXITSTATUS(status));
	exit_status(SET, status);
}
