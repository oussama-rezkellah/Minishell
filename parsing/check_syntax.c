/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 00:54:01 by orezkell          #+#    #+#             */
/*   Updated: 2024/11/01 03:14:14 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	print_syntax_error(t_lst_toks *tok)
{
	char	*str;

	str = "\0";
	if (tok->type == PIPE)
		str = "|";
	else if (tok->type == HEREDOC)
		str = "<<";
	else if (tok->type == APPEND)
		str = ">>";
	else if (tok->type == OUT) 
		str = ">";
	else if (tok->type == IN)
		str = "<";
	else if (tok->type == LPR)
		str = "(";
	else if (tok->type == RPR)
		str = ")";
	else if (tok->type == AND)
		str = "&&";
	else if (tok->type == OR)
		str = "||";
	else if (tok->type == WORD)
		str = tok->content;
	printf("bash: syntax error near unexpected token '%s'\n", str);
}

// typedef enum e_token
// {
// 	PIPE = 1 , //1
// 	HEREDOC = 2, //2
// 	APPEND = 3, //3
// 	OUT = 4, //4
// 	IN = 5, //5
// 	LPR = 6, //6
// 	RPR = 7, //7
// 	AND = 8, //8
// 	OR = 9, //9
// 	WORD = 10//10
// }tok;


// //PIPE	//HER	//APP	//OUT	//IN	//LPR	//RPR	//AND	//OR	//WORD
// {0		,3		,3		,3		,3		,4		,0		0,		0,		2		}, //state 1,inital
// (6		,3		,3		,3		,3		,0		,5		6,		6,		2		), //state 2,after word
// (0		,0		,0		,0		,0		,0		,0		0,		0,		2		),//state 3,after redir
// (0		,3		,3		,3		,3		,4		,0		0,		0,		2		),//state 4, after LPR
// (6		,0		,0		,0		,0		,0		,5		6,		6,		0		),//state 5, after RPR
// {0		,3		,3		,3		,3		,4		,0		0,		0,		2		},//state 6, after OP

//bash: syntax error: unclosed parentheses

int	get_state (int prev_state, int tok)
{
	int tr[6][10] = {
		{0, 3, 3, 3, 3, 4, 0, 0, 0, 2},
		{6, 3, 3, 3, 3, 0, 5, 6, 6, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
		{0, 3, 3, 3, 3, 4, 0, 0, 0, 2},
		{6, 0, 0, 0, 0, 0, 5, 6, 6, 0},
		{0, 3, 3, 3, 3, 4, 0, 0, 0, 2}
	};

	return tr[prev_state - 1][tok - 1];
}

int check_syntax(t_lst_toks *lst)
{
	t_lst_toks *tmp = lst;
	int state = 1;
	int paren_count = 0;

	while (tmp)
	{
		state = get_state(state, tmp->type);
		if (tmp->type == LPR)
			paren_count++;
		else if (tmp->type == RPR)
		{
			if (paren_count == 0)
			{
				print_syntax_error(tmp);
				return (0);
			}
			paren_count--;
		}
		if (!state)
		{
			print_syntax_error(tmp);
			return (0);
		}
		tmp = tmp->next;
	}
	if (paren_count != 0)
	{
		printf("bash: syntax error: unclosed parentheses\n");
		return (0);
	}
	else if (state != 2 && state != 5)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}