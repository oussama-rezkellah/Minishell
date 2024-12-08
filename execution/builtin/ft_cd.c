
#include "../../inc/minishell.h"

void cd_home (t_env **env)
{
	char *current;
	char *home;

	current = getcwd(NULL, 0);
	if (!current)
		current = env_get(env, "PWD");
	home = env_get(*env, "HOME");
	if (!home)
	{
		printf_fd(2, "cd: HOME not set\n");
		return (free(current));
	}
	if (chdir(home))
	{
		printf_fd(2, "cd: ", home);
		perror("");
		return (free(current));
	}
	env_set(env, "PWD", home);
	env_set(env, "OLDPWD", current);
	free(current);
}

void	cd_old(t_env *env)
{
	char *current;

	current = getcwd(NULL, 0);
	if (!env_get(env, "OLDPWD"))
	{
		free(current), printf_fd(2, "cd: OLDPWD not set\n");
		return ;
	}
	if (chdir(env_get(env, "OLDPWD")))
	{
		free(current), perror("cd: ");
		return ;
	}
	env_set(&env, "PWD", env_get(env, "OLDPWD"));
	if (current)
		env_set(&env, "OLDPWD", current);
	else
		env_set(&env, "OLDPWD", "");
	free(current), printf_fd(1, env_get(env, "PWD"));
}

int check_path(char *p)
{
	int i;

	i = 0;
	while (p[i])
	{
		if (p[i] != '/' && p[i] != '.')
			return (1);
		i++;	
	}
	return (0);
}

char *get_a_valid_path(t_env *env, char *p)
{
	int i;
	
	i = 0;
	if (!p)
		return (NULL);
	while (p[i])
		i++;
	i--;
	while (i > 0)
	{
		if (p[i] == '/')
		{
			p[i] = 0;
			if (!chdir (p))
				break;
		}
		i--;
	}
}

void	cd(t_env *env, char *p)
{
	char current[1024];
	char *pwd;

	if(!getcwd(current, sizeof(current)))
	{
		env_set(&env, "OLDPWD", env_get(env, "PWD"));
		if(check_path(p))
			if (chdir (p))
				perror("cd :");
		p = get_a_valid_path(env, env_get(env, "PWD"));
	}
	if (chdir(p))
		return (perror("cd :"));
	env_set(&env, "OLDPWD", current);
	getcwd(current, sizeof(current));
	env_set(&env, "PWD", current);
}

void    ft_cd(char **cmd , t_env **env)
{
	char *current;

	if (!env_get(env, "PWD"))
	{
		current = getcwd(NULL, 0);
		env_set(env , "PWD", current);
		free(current);
	}
	if (!cmd[1] || !ft_strncmp (cmd[1], "~", 2))
		return (cd_home(env));
	else if (!ft_strncmp(cmd[1], "-", 2))
		return (cd_old(env));
	else if (!ft_strncmp(cmd[1], ".", 2))
		return (env_set(&env,  "OLDPWD", env_get(env, "PWD")));
	cd(env, cmd[1]);
}