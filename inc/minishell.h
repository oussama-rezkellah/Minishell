/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 02:46:50 by orezkell          #+#    #+#             */
/*   Updated: 2024/11/01 03:05:39 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# include <unistd.h>
# include <limits.h>
# include <libc.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "ft_printf.h"
# include "garbage_collector.h"

// # define MAL 0
// # define CLEAR 2
// # define MAL_ENV 1
// # define CLEAR_ENV 3 

// typedef struct s_memory
// {
// 	void			*address;
// 	struct s_memory	*next;
// }	t_memory;

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
	WORD = 10//10
}tok;

typedef struct s_toks
{
    tok type;
    char *content;
    struct s_toks *next;
}t_lst_toks;

typedef struct s_env
{
	char            *env;
	char            *name;
	char            *value;
	struct s_env    *next;
}	t_env;

typedef struct s_minishell
{
	t_env		*env;
	t_lst_toks 	*tokens;
}	t_minishell;

void	initialise_env (t_env **new_env, char **env);
void	array_to_lst(char **env, t_env **new_env);
char	**lst_to_array(t_env *lst_env);
char	*ft_strdup_env(const char *s1);
t_env	*lstnew_env(char *value, char *name, char *env);
void	lst_addback_env(t_env **new_env, t_env *new);
size_t    lstsize_env(t_env *lst_env);


int 	ft_isspace(int c);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);

tok	get_type (char **str);
tok	check_type (char *str);
int	len_unquoted (char *str);
int	len_quoted (char *str, char quote);
t_lst_toks	*ft_toknew(void *content, tok type);
void	add_tok_back(t_lst_toks **lst, t_lst_toks *new);
t_lst_toks *tokenize (char **str);
int check_syntax(t_lst_toks *lst);



int    parsing(t_minishell *sh,char *input);

#endif