/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 12:32:30 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/12 18:49:31 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>

static void 		init_zone(t_zone *zone, size_t size)
{
	t_block *first_block;

	first_block = (t_block*)((void*)zone + META_ZONE_SIZE + 1);
	ft_printf("First block of zone : %p\n", first_block);
	first_block->size = size - (META_ZONE_SIZE + META_BLOCK_SIZE);
	first_block->is_free = 1;
	first_block->next = NULL;
	first_block->prev = NULL;
	zone->type = get_zone_type(size);
	zone->size = META_ZONE_SIZE + META_BLOCK_SIZE;
	zone->block_lst = first_block;
	zone->next = NULL;
}

t_zone				*create_alloc_zone(size_t size)
{
	t_zone	*new;
	t_zone	*tmp;

	if ((new = mmap(0, size, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	ft_printf("Address allocated : %p, size : %zu\n", new, size);
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

void				*ft_malloc(size_t size)
{
	void			*ptr;

	// ft_printf("\n/// ft_malloc debug \\\\\\\nMETA_BLOCK_SIZE : %zu\nMETA_ZONE_SIZE : %zu\nMAX_ALLOC_SIZE : to define..\n", META_BLOCK_SIZE, META_ZONE_SIZE);
	if (!g_alloc_start)
	{
		if (!(create_alloc_zone(TINY_SIZE)))
			return (NULL);
		if (!(create_alloc_zone(SMALL_SIZE)))
			return (NULL);
	}
	ptr = get_allocated_ptr(size);
	return (ptr);
}
