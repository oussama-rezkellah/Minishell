/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:27:05 by orezkell          #+#    #+#             */
/*   Updated: 2024/08/25 23:36:27 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H

# define GARBAGE_COLLECTOR_H
# include "ft_printf.h"
# include <stdlib.h>
# include <errno.h>
# include <string.h>

# define MAL 0
# define CLEAR 2
# define MAL_ENV 1
# define CLEAR_ENV 3 

typedef struct s_memory
{
	void			*address;
	struct s_memory	*next;
}	t_memory;

void	*ft_malloc (size_t n, int flag);

#endif