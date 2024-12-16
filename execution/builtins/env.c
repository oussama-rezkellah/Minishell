
#include "../../inc/minishell.h"

int env_cmd(t_env *env)
{
	if (!env)
		return (1);
	while (env)
	{
		if (env->name && env->value)
			printf_fd(1, "%s=%s\n", env->name, env->value);
		env = env->next;
	}
    return (0);
}
