/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-hss <aben-hss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:26:55 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/21 06:45:23 by aben-hss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int exit_status(t_exit flag, int new_exit_status)
{
	static int	exit_status;

	if (flag == GET)
		return (exit_status);
	if (flag == SET)
	{
		// puts("here");
		exit_status = new_exit_status;
	}
	return (0);
}
