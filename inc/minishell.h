/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 02:46:50 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/20 02:40:03 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdint.h>
# include <ctype.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "ft_printf.h"
# include "garbage_collector.h"
# include <signal.h>
# include <string.h>
# include <termios.h>
# include <sys/param.h>

typedef enum e_token
{
	PIPE = 1 , //1
	HEREDOC = 2, //2
	APPEND = 3, //3
	OUT = 4, //4
	IN = 5, //5
	LPR = 6, //6
	RPR = 7, //7
	AND = 8, //8
	OR = 9, //9
	WORD = 10,//10
	CMD = 11
}		t_tok;

typedef enum s_mode
{
	APPEND_MODE,
	SET_MODE
}			t_mode;

typedef enum s_exit_status
{
	SET,
	GET,
}				t_exit;

typedef struct s_toks
{
	t_tok			type;
	char			*content;
	struct s_toks	*next;
}	t_lst_toks;

typedef struct s_redir
{
	t_tok			type;
	char			*file;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_tree
{
	t_tok			type;
	char			*p_cmd;
	int				fd_in;
	int				fd_out;
	t_redir			*redir;
	struct s_tree	*l_child;
	struct s_tree	*r_child;
}	t_tree;

typedef struct s_stack
{
	t_tree			*node;
	struct s_stack	*next;
}	t_stack;

typedef struct s_env
{
	char			*env;
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	t_env		*env;
	t_lst_toks	*tokens;
	t_tree		*tree;
	int			exit_status;
}	t_minishell;

int			g_heredoc_signal;

void		signals_init(void);
void		heredoc_sigint(int sig);
void		handle_sigint(int signal);
int			ft_wait(int l_pid, int r_pid, int *status);

int			exit_status(t_exit flag, int new_exit_status);

void		initialise_env(t_env **new_env, char **env);
void		array_to_lst(char **env, t_env **new_env);
void		shlvl(t_env **env);
char		**lst_to_array(t_env *lst_env);
char		*ft_strdup_env(const char *s1);
t_env		*lstnew_env(char *value, char *name, char *env);
t_env		*create_env(char *value, char *name);
void		lst_addback_env(t_env **new_env, t_env *new);
size_t		lstsize_env(t_env *lst_env);
char		*env_get(t_env *env, char *name);
void		env_set(t_env **env, char *name, char *value);

int			ft_isspace(int c);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_env(char const *s1, char const *s2);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
char		*ft_strtrim(char const *s1, char const *set);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strndup(const char *s, size_t n);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strcat(char *dst, const char *src);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
char		**ft_split(char const *s, char c);

t_tok		get_type(char **str);
t_tok		check_type(char *str);
int			len_unquoted(char *str);
int			len_quoted(char *str, char quote);
t_lst_toks	*ft_toknew(void *content, t_tok type);
void		add_tok_back(t_lst_toks **lst, t_lst_toks *new);
t_lst_toks	*tokenize(char **str);
int			check_syntax(t_lst_toks *lst);

t_redir		*ft_redirnew(void *content, t_tok type);
void		add_redir_back(t_redir **lst, t_redir *new);
t_tree		*ft_nodenew(void *content, t_redir	*redir, t_tok type);
void		add_node_back(t_tree **lst, t_tree *new);
void		build_tree(t_minishell *sh);

void		push(t_tree **stack, t_tree *to_push);
void		push_back(t_tree **stack, t_tree *to_push);
int			pop(t_tree **stack);
void		push_back_pop(t_tree **stack, t_tree **to_push);
int			get_pre(t_tok op);

t_stack		*ft_nodestack_new(void *content, t_redir *redir, t_tok type);
void		push_s(t_stack	**stack, t_tree *to_push);
t_tree		*pop_s(t_stack	**stack);

int			parsing(t_minishell *sh, char *input);
// execution
void		execution(t_tree *node, t_env **env);
void		pipe_exec(t_tree *node, t_env **env);
void		cmd_exec(t_tree *node, t_env **env);
int			open_fill_fds(t_tree *cmd);
int			handle_exec_err(char *cmd, int errno_val);
int			open_all_heredocs(t_minishell *sh);
int			ft_heredoc(char *del, t_env *env);

//expnad
char *replace_values(char **str, t_env *env);
char **ft_expand(t_tree *node, t_env *env);
char **split_cmd(char *s);
char **remove_q_cmd(char **cmd);

// builtins
int			is_builtin(char *cmd);
int			execute_builtin(char **cmd, t_env *env);
void		get_set_cwd(t_exit mode, char *new_cwd, char **old_cwd);
int			is_valid_name(char *name);
int			export_cmd(char **argv, t_env **env);
int			echo_cmd(char **arguments);
int			cd_cmd(t_env *env, char **argv);
int			pwd_cmd(char **args);
int			env_cmd(t_env *env);
int			exit_cmd(char **argv, int exit_status);
int			unset_cmd(t_env **env, char **argv);

#endif
