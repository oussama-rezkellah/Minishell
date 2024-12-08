#include "../inc/minishell.h"

int	l_r_child(t_tree *command, int pipe_fd[2], int flag, t_env **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return pid;
	else if (pid == 0)
	{
		if (flag == 0)
			dup(pipe_fd[1], STDOUT_FILENO);
		else if (flag == 1)
			dup(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execution(command, env);
		exit(*exit);
	}
	return (pid);
}

void pipe_exec(t_tree *command, t_env **env, int *exit)
{
    pid_t	l_child;
    pid_t	r_child;
	int		pipe_fd[2];
	int		status;

	if (pipe(pipe_fd[2]) < 0)
		return ;
	l_child = l_r_child(command->l_child, pipe_fd, 0, env);
	r_child = l_r_child(command->r_child, pipe_fd, 0, env);
	if (l_child < 0)
		return ;
	if (r_child < 0)
		return ;
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(l_child, &status, 0);
	waitpid(r_child, &status, 0);
	set_exit_status(status);
}
