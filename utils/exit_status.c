/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:26:55 by orezkell          #+#    #+#             */
/*   Updated: 2024/12/05 12:27:59 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int exit_status(t_exit flag, int new_exit_status)
{
	static int	exit_status;

	if (flag == GET)
		return (exit_status);
	exit_status = new_exit_status;
	return (0);
}