#include "../../inc/minishell.h"

static int extract_var_name(char* input, char** var_name)
{
	int j = 0;
	int i = -1;
	while (ft_isalnum(*(input + j)) || *(input + j) == '_')
		j++;
	*var_name = ft_malloc(j + 1, MAL);
	while (++i < j)
		(*var_name)[i] = input[i];
	(*var_name)[i] = 0;
	return j;
}

static char* handle_var(char *ret, int *i, char* input, t_env *env)
{
	char	*tmp;
	char	*var_name;
	char	*var_value;

	tmp = ft_strdup (" ");
	var_name = NULL;
	var_value = NULL;
	(*i)++;
	if (input[*i] == '?')
		return (*i)++,ft_strjoin(ret, ft_itoa(exit_status(GET,0)));
	if(ft_isalpha(input[*i]) || input[*i] == '_')
	{
		*i = *i + extract_var_name(input + (*i), &var_name);
		var_value = env_get(env ,var_name);
		if (var_value)
			return ft_strjoin(ret, var_value);
		return ret;
	}
	tmp[0] = '$';
	return ft_strjoin(ret, tmp);
}

static char* process_char(char *ret, int *i, char* input, t_env *env)
{
	char	*tmp;
	tmp = ft_strdup(" ");

	if (input[*i] == '$')
		return (handle_var(ret, i ,input, env));
	tmp[0] = input[*i];
	return (*i)++,ft_strjoin(ret, tmp);
}

char *expand_heredoc(char *line, t_env *env)
{
    char *to_ret = ft_strdup("");
    int i = 0;

	while (line[i])
		to_ret = process_char(to_ret, &i,line, env);
	return (to_ret);
}

char *expand_del(char *del, int *flag)
{
    char *ret;

    ret = remove_q_line(del);
    if (ft_strlen(del) != ft_strlen(ret))
        *flag = 1;
    else
        *flag = 0;
    return (ret);
}