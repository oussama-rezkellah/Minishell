
#include "../../inc/minishell.h"

void    get_set_cwd(t_exit mode, char *new_cwd, char *old_cwd)
{
    static char *cwd;
    char    *tmp;

    if (!cwd)
    {
        tmp = getcwd(NULL, 0);
        cwd = ft_strdup(tmp);
        free(tmp);
    }
    if (mode == SET)
        cwd = ft_strdup(new_cwd);
    else if (mode == GET)
    {
        tmp = ft_strdup(cwd);
        old_cwd = tmp;
        new_cwd = old_cwd;
    }
}

int	pwd_cmd(char **args)
{
	char    *cwd;

	if (args[1] != NULL)
		return(printf_fd(2, "pwd: too many arguments\n"), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
    {
        cwd = ft_strdup("");
        get_set_cwd(GET, NULL, cwd);
        if (!cwd)
            return (perror("getcwd"), 1);
    }
	printf_fd(1, "%s\n", cwd);
	return (free(cwd), 0);
}