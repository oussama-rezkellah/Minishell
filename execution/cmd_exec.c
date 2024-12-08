#include "../inc/minishell.h"

void	closefiles(int *arr_fd)
{
	int	i;

	i = 0;
	while (arr_fd[i] != -1)
	{
		close(arr_fd[i]);
		i++;
	}
}

int		file_output(t_tree *command, t_redir *redir, int *index)
{
	int	fd;
	
	if (redir->type == 4)
		fd = open(redir->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (redir->type == 3)
		fd = open(redir->file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		printf_fd(2, redir->file);
		printf_fd(2, ": No such file or directory\n");
		return (1);
	}
	command->in_out[1] = fd;
	command->arr[*index] = fd;
	return (0);
}

int		file_input(t_tree *command, char *file, int *index)
{
	int	fd;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf_fd(2, file);
		printf_fd(2, ": No such file or directory\n");
		return (1);
	}
	command->in_out[0] = fd;
	command->arr[*index] = fd;
	return (0);
}

int		openfiles(t_tree *command, t_redir *redir)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	while (redir)
	{
		if (redir->type == 5 || redir->type == 2)
		{
			if (file_input(command, redir->file, &i))
				return (-1);
		}
		else if (redir->type == 4 || redir->type == 3)
		{
			if (file_output(command, redir, &i))
				return (-1);
		}
		i++;
		redir = redir->next;
	}
	return (command->arr[i] = -1, 0);
}

void	exec_sys(t_tree *command, char **env)
{
	execve(command->cmd[0], command->cmd, env);
	printf_fd(2, command->cmd[0]);
	printf_fd(2, ": ");
	perror("");
	if (access(command->cmd[0], F_OK))
		exit(127);
	exit(126);
}

char	*get_path(char **env)
{
	int	i;

	i = -1;
	if (!env)
		return (NULL);
	while (env[++i])
	{
		if (ft_strncmp(env[++i], "PATH=", 5) == 0)
			return (ft_strnstr((env[i], "/", 6)));
	}
	return (NULL);
}

int		find_slash(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '/')
			return (0);
	}
	return (1);
}

int		join_path_cmd(t_tree **command, char **env)
{
	int		i;
	char	**split;
	char	*cmd;

	i = 0;
	if (find_slash((*command)->cmd[0]) == 0)
		return (0);
	split = ft_split(get_path(env), ';');
	if (!split)
		return (1);
	while (split[i])
	{
		cmd = ft_strjoin(split[i], "/");
		cmd = ft_strjoin(cmd, (*command)->cmd[0]);
		if (access(cmd, F_OK | X_OK) != -1)
			return ((*command)->cmd[0] = cmd, 0);
		free(split[i]);
		i++;
		if (!split[i])
			printf_fd(2, "Command not found\n");
	}
	return (1);
}

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int		check_builtins(t_tree *command)
{
	if (!ft_strcmp("cd", command->cmd[0]))
		ft_cd();
	else if (!ft_strcmp("echo", command->cmd[0]))
		ft_echo();
	else if (!ft_strcmp("env", command->cmd[0]))
		env();
	els e if (!ft_strcmp("exit", command->cmd[0]))
		exit();
	else if (!ft_strcmp("export", command->cmd[0]))
		export();
	else if (!ft_strcmp("pwd", command->cmd[0]))
		pwd();
	else if (!ft_strcmp("unset", command->cmd[0]))
		unset();
	else
		return (0);
	return (exit_status);
}

void    handle_exit_status(int *status)
{
    if (WIFSIGNALED(status))
    {
        if (WTERMSIG(status) == SIGINT)
            printf_fd(2, "\n");
        else if (WTERMSIG(status) == SIGQUIT)
            printf_fd("Quit: 3\n", 2);
        exit_status(SET, WTERMSIG(status) + 128);
    }
    else
        exit_status(SET, WEXITSTATUS(status));
}

void	cmd_exec(t_tree *command, t_env *env)
{
	int		pid;
	char	**env;
	int 	status;

	expand_cmd(command, env);
	env = lst_to_array(env);
	if (openfiles(command, command->redir) == -1 || !check_builtins(command))
		return ;
	pid = fork();
	if (pid < 0)
		return ;
	else if(!pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (!join_path_cmd(&command, env))
			return (_closefiles(command->arr), exit (127));
		if (command->in_out[1] != 1)
			dup2(command->in_out[1], STDOUT_FILENO);
		if (command->in_out[0] != 0)
			dup2(command->in_out[0], STDIN_FILENO);
		_closefiles(command->arr);
		exec_sys(command, env);
	}
	waitpid(pid, &status, 0);
	handle_exit_status(&status);
}
