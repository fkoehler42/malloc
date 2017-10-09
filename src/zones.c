/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 14:55:35 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/09 15:37:41 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>

static void		init_zone(t_zone *zone, size_t size)
{
	t_block *first_block;

	first_block = (t_block*)((void*)zone + META_ZONE_SIZE);
	first_block->canary = CANARY(first_block->canary);
	first_block->size = size - (META_ZONE_SIZE + META_BLOCK_SIZE);
	first_block->is_free = 1;
	first_block->next = NULL;
	first_block->prev = NULL;
	zone->canary = CANARY(zone->canary);
	zone->type = get_zone_type(size);
	zone->size = META_ZONE_SIZE + META_BLOCK_SIZE;
	zone->block_lst = first_block;
	zone->prev = NULL;
	zone->next = NULL;
}

static void		insert_zone_into_list(t_zone *zone)
{
	t_zone	*tmp;

	if (!(tmp = g_alloc.heap))
		g_alloc.heap = zone;
	else if (g_alloc.heap > zone)
	{
		check_data_validity((void*)g_alloc.heap, ZONE);
		zone->next = g_alloc.heap;
		g_alloc.heap = zone;
	}
	else
	{
		check_data_validity((void*)tmp, ZONE);
		while (tmp->next && tmp->next < zone && (tmp = tmp->next))
			check_data_validity((void*)tmp, ZONE);
		zone->next = tmp->next;
		tmp->next = zone;
		zone->prev = tmp;
	}
	if (zone->next)
		zone->next->prev = zone;
}

t_zone			*create_zone(size_t size)
{
	t_zone	*new;

	if ((new = (t_zone*)mmap(0, size, PROT_READ | PROT_WRITE,
	MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
	{
		put_alloc_error(MAPPING_FAILED, size);
		return (NULL);
	}
	init_zone(new, size);
	insert_zone_into_list(new);
	return (new);
}

int				delete_zone(t_zone *zone)
{
	t_zone	*prev;
	t_zone	*next;
	size_t	size;

	prev = zone->prev;
	next = zone->next;
	if (zone->type == LARGE)
		size = zone->size;
	else
		size = (zone->type == TINY) ? TINY_SIZE : SMALL_SIZE;
	if (munmap(zone, size) < 0)
	{
		put_error(UNMAPPING_FAILED, zone);
		return (-1);
	}
	if (!prev)
	{
		if ((g_alloc.heap = next))
			g_alloc.heap->prev = NULL;
		return (0);
	}
	if (next)
		next->prev = prev;
	prev->next = next;
	return (0);
}
