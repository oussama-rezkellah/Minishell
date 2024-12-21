#include "../../inc/minishell.h"

char **ft_expand(t_tree *node, t_env *env)
{
    char **cmd;
    if (!node->p_cmd)
        return (NULL);
    node->p_cmd = replace_values(&node->p_cmd, env);
    cmd = split_cmd (node->p_cmd);
    return(remove_q_cmd(cmd));
}
