/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:25:57 by orezkell          #+#    #+#             */
/*   Updated: 2024/10/26 18:30:51 by orezkell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/garbage_collector.h"

void	*malloc_error(int err)
{
	printf_fd (2, "bash: malloc: %s\n", strerror(err));
	exit (1);
	return (NULL);
}

void	*new_memory (void *address)
{
	t_memory	*new_memory;

	new_memory = malloc (sizeof(t_memory));
	if(!new_memory)
		return (NULL);
	new_memory->address = address;
	new_memory->next = NULL;
	return (new_memory);
}

int	ft_add_to_memory(t_memory **memory, void *address)
{
	t_memory	*last;

	if (!*memory)
	{
		*memory = new_memory(address);
		if (!(*memory))
			return (0);
	}
	else
	{
		last = *memory;
		while (last->next)
			last = last->next;
		last->next = new_memory(address);
		if (!last->next)
			return (0);
	}
	return (1);
}

void    ft_clear_memory(t_memory **memory)
{
	t_memory *tracker;
	t_memory *tmp;

	tracker = *memory;
	while (tracker)
	{
		tmp = tracker->next;
		free(tracker->address);
		tracker->address = NULL;
		free(tracker);
		tracker = NULL;
		tracker = tmp;
	}
}

void	*ft_malloc(size_t n, int flag)
{
	static t_memory	*memory;
	static t_memory	*memory_env;
	void			*to_return;

	to_return = NULL;
	if (flag == MAL)
	{
		to_return = malloc(n);
		if (!to_return)
			return (ft_clear_memory(&memory), ft_clear_memory(&memory_env), malloc_error(errno));
		if (!ft_add_to_memory(&memory, to_return))
			return (ft_clear_memory(&memory), ft_clear_memory(&memory_env), malloc_error(errno));
	}
	if (flag == MAL_ENV)
	{
		to_return = malloc(n);
		if (!to_return)
			return (ft_clear_memory(&memory), ft_clear_memory(&memory_env), malloc_error(errno));
		if (!ft_add_to_memory(&memory_env, to_return))
			return (ft_clear_memory(&memory), ft_clear_memory(&memory_env), malloc_error(errno));
	}
	else if (flag == CLEAR)
		ft_clear_memory (&memory);
	else if (flag == CLEAR_ENV)
		ft_clear_memory (&memory_env);
	return (to_return);
}
