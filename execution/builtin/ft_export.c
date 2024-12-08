/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 23:39:50 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/08 00:31:35 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *get_name_export (char *cmd, int *i)
{
	int c;
	char *to_ret;
	
	while (cmd[*i] && cmd[*i] != '=' && (cmd[*i] != '+' || cmd[*i +1] != '='))
		(*i)++;
	to_ret = ft_malloc(*i + 1, MAL);
	c = -1;
	while (++c < *i)
		to_ret[c] = cmd[c];
	to_ret[c] = 0;
	return (to_ret);
}

char *get_value_export (char *cmd, int *i)
{
	int c;
	int	tracker;
	char *to_ret;
	
	c = 0;
	if (cmd[*i + c] == '=')
		(*i)++;
	else if ((cmd[*i + c] == '+' && cmd[*i + c+1] == '='))
		*i = *i + 2;
	while (cmd[*i + c])
		c++;
	to_ret = ft_malloc(c + 1, MAL);
	tracker = -1;
	while (++tracker < c)
		to_ret[tracker] = cmd[tracker];
	to_ret[tracker] = 0;
	return (to_ret);
}

int	check_name(char *name)
{
	if (name[0])	
}

int	parse_export(char *cmd, char **name ,char **value);
{
	int	op;
	int i;

	i = 0;
	*name = get_name_export (cmd, &i);
	if (check_name (*name));
		return (-1)
	if (cmd[*i] == '=')
		op = 0;
	else if (cmd[*i] == '+')
		op = 1;
	else if (!cmd[*i])
		return (*value = NULL, 0);
	*value = get_value_export (cmd, &i);
	return (op);
}
void	parse_and_execute(char *cmd, t_env **env)
{
	char 	*name;
	char	*value;
	int		op;

	op = parse_export(cmd , &name , &value);
	if (op < 0)
		return ;
}

void    ft_export(char **cmd, t_env **env)
{
	int	i;

	i = 1;
	if (!cmd[i])
		//return (print_export(env));
	while(cmd[i])
		parse_and_execute(cmd[i++], env);
}