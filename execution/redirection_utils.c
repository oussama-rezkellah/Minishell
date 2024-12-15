/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:13:26 by aben-hss          #+#    #+#             */
/*   Updated: 2024/12/10 22:42:50 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

int	ft_heredoc(char *del, t_env *env)
{
	int		fd[2];
	char	*line;
	char	*newline;
	int		fd_in;
	// int		flag;

	(void)env;
	// flag = 1;
	fd_in = dup(0);
	if (pipe(fd) == -1)
		return (-1);
	// register signal

	// determine expand flag
	// del = expand_flag(del, &flag);
	while (1)
	{
		line = readline("> ");
		// check for g_heredoc_sig
		// break if so
		if (!line || !ft_strncmp(line, del, strlen(del)))
			return (free(line), close(fd_in), close(fd[1]), fd[0]);
		// TODO logic for heredoc expansion
		// if (!flag)
		// 	newline = expand_heredoc(line, env);
		// else
			newline = line;
		if (!newline)
			newline = "";
		write(fd[1], newline, ft_strlen(newline));
		write(fd[1], "\n", 1);
		free(line);
	}
	// check for g_heredoc_sig
	// free and close all
	return (free(line), close(fd[1]), fd[0]);
}
