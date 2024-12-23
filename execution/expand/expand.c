#include "../../inc/minishell.h"

int expand_redir(t_tree *node, t_env *env)
{
    t_redir *redir;
    char    **tmp;

    redir = node->redir;
    while (redir)
    {
        if (redir->type != HEREDOC)
        {
            node->redir->file = replace_values(&node->redir->file, env);
            tmp = split_cmd (node->redir->file);
            if (!tmp[0][0] || tmp[1])
                ;//set_exit_status and print ambiguous and return 0
            node->redir->file = remove_q_line(tmp[0]);
        }
        redir = redir->next;
    }
    return(1);
}

char **ft_expand(t_tree *node, t_env *env)
{
    char **cmd;
    if (!node->p_cmd)
        return (NULL);
    node->p_cmd = replace_values(&node->p_cmd, env);
    cmd = split_cmd (node->p_cmd);
    if (!expand_redir(node, env))
        return (NULL);
    return(remove_q_cmd(cmd));
}
