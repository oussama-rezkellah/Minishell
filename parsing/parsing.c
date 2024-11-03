/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 23:53:57 by orezkell          #+#    #+#             */
/*   Updated: 2024/11/03 14:48:45 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// #define RED     "\x1b[31m"
// #define GREEN   "\x1b[32m"
// #define YELLOW  "\x1b[33m"
// #define BLUE    "\x1b[34m"
// #define RESET   "\x1b[0m"

// void print_token_colored(t_tree *node)
// {
//     if (node->type == CMD)
//         printf(GREEN "%s" RESET, node->p_cmd);
//     else if (node->type == AND)
//         printf(YELLOW "&&" RESET);
//     else if (node->type == OR)
//         printf(RED "||" RESET);
//     else if (node->type == PIPE)
//         printf(BLUE "|" RESET);
// }

// void print_tree_recursive(t_tree *root, int level, char *prefix, int is_left)
// {
//     if (!root)
//         return;

//     printf("%s", prefix);
//     printf("%c-- ", is_left ? '`' : ',');
//     print_token_colored(root);
//     printf("\n");

//     char new_prefix[1024];
//     sprintf(new_prefix, "%s%c   ", prefix, is_left ? ' ' : '|');

//     print_tree_recursive(root->r_child, level + 1, new_prefix, 0);
//     print_tree_recursive(root->l_child, level + 1, new_prefix, 1);
// }

// void test_tree(t_tree *root)
// {
//     printf("\nTree Structure:\n");
//     print_tree_recursive(root, 0, "", 1);
// }
int	parsing(t_minishell *sh, char *input)
{
	char	*line;

	line = ft_strtrim (input, " \t\n\v\r\f");
	free(input);
	sh->tokens = NULL;
	sh->tokens = tokenize (&line);
	if (!sh->tokens)
		return (0);
	if (!check_syntax (sh->tokens))
		return (0);
	build_tree(sh);
	return (1);
}
