/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 14:55:35 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/14 17:39:21 by flav             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>

static void 		init_zone(t_zone *zone, size_t size)
{
	t_block *first_block;

	first_block = (t_block*)((void*)zone + META_ZONE_SIZE);
	// ft_printf("First block of zone : %p\n", first_block);
	first_block->size = size - (META_ZONE_SIZE + META_BLOCK_SIZE);
	first_block->is_free = 1;
	first_block->next = NULL;
	first_block->prev = NULL;
	zone->type = get_zone_type(size);
	zone->size = META_ZONE_SIZE + META_BLOCK_SIZE;
	zone->block_lst = first_block;
	zone->next = NULL;
}

t_zone				*create_zone(size_t size)
{
	t_zone	*new;
	t_zone	*tmp;

	if ((new = mmap(0, size, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	ft_printf("New zone allocated : %p, size : %zu\n", new, size);
	init_zone(new, size);
	if (!(tmp = g_alloc_start))
		g_alloc_start = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}
