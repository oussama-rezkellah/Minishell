/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 23:53:57 by orezkell          #+#    #+#             */
/*   Updated: 2024/10/27 23:55:15 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	parsing(t_minishell *sh, char *input)
{
	char	*line;

	line = ft_strtrim (input, " \t\n\v\r\f");
	free(input);
	sh->tokens = NULL;
	sh->tokens = tokenize (&line);
}
	// while (sh->tokens)
	// {	
	// 	printf ("%d\n",sh->tokens->type);
	// 	printf ("%s\n",sh->tokens->content);
	// 	sh->tokens = sh->tokens->next;
	// }