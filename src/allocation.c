/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 17:48:00 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/09 15:32:54 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*alloc_new_block(t_zone *zone, t_block *free_block, size_t size)
{
	size_t	min_block_size;
	t_block	*new_block;

	min_block_size = get_min_block_size(zone->type);
	if (free_block->size < (size + min_block_size))
	{
		new_block = free_block;
		zone->size += new_block->size;
	}
	else
	{
		new_block = split_block(free_block, size);
		zone->size += (size + META_BLOCK_SIZE);
	}
	new_block->is_free = 0;
	return (new_block);
}

static t_block	*find_free_block(size_t size, t_size_type block_type)
{
	t_block	*block;
	t_zone	*zone;
	size_t	total_zone_size;

	zone = g_alloc.heap;
	while (zone)
	{
		check_data_validity((void*)zone, ZONE);
		total_zone_size = (zone->type == TINY) ? TINY_SIZE : SMALL_SIZE;
		if (zone->type == block_type && (total_zone_size - zone->size) >= size)
		{
			block = zone->block_lst;
			while (block)
			{
				check_data_validity((void*)block, BLOCK);
				if (block->is_free && block->size >= size)
					return (alloc_new_block(zone, block, size));
				block = block->next;
			}
		}
		zone = zone->next;
	}
	return (NULL);
}

void			*get_allocated_ptr(size_t size)
{
	t_size_type	block_type;
	t_block		*alloc_block;
	t_zone		*new_zone;

	alloc_block = NULL;
	new_zone = NULL;
	size = get_rounded_block_size(size);
	if ((block_type = get_block_type(size)) == LARGE)
		new_zone = create_zone(size + META_ZONE_SIZE + META_BLOCK_SIZE);
	else if (!g_alloc.heap
	|| !(alloc_block = find_free_block(size, block_type)))
	{
		if (block_type == TINY)
			new_zone = create_zone(TINY_SIZE);
		else if (block_type == SMALL)
			new_zone = create_zone(SMALL_SIZE);
	}
	if (new_zone)
		alloc_block = alloc_new_block(new_zone, new_zone->block_lst, size);
	if (!alloc_block)
		return (NULL);
	return ((void*)alloc_block + META_BLOCK_SIZE);
}

void			*realloc_process(void *ptr, size_t size, t_zone *zone)
{
	t_block		*block;
	size_t		old_size;
	size_t		min_block_size;
	t_size_type	realloc_type;

	block = (t_block*)(ptr - META_BLOCK_SIZE);
	old_size = block->size;
	size = get_rounded_block_size(size);
	min_block_size = get_min_block_size(zone->type);
	realloc_type = get_block_type(size);
	if (realloc_type != zone->type)
		return (get_dup_block_ptr(block, size, old_size));
	if (size == old_size || (size < old_size && (zone->type == LARGE
	|| old_size <= min_block_size || (old_size - min_block_size) < size)))
		return (ptr);
	if (size < old_size)
	{
		return ((void*)reduce_block(block, size, &zone->size)
		+ META_BLOCK_SIZE);
	}
	if ((enlarge_block(block, size, &zone->size, min_block_size) != NULL))
		return (ptr);
	return (get_dup_block_ptr(block, size, old_size));
}
