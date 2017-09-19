/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 17:48:00 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/19 11:26:48 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*alloc_new_block(t_zone *zone, t_block *free_block, size_t size)
{
	size_t	min_block_size;
	t_block	*new_block;

	min_block_size = get_min_block_size(zone->type);
	if (free_block->size == size || free_block->size < (size + min_block_size))
	{
		new_block = free_block;
		zone->size += size;
	}
	else
	{
		new_block = split_and_add_block(free_block, size);
		zone->size += (size + META_BLOCK_SIZE);
	}
	new_block->is_free = 0;
	return (new_block);
}

static t_block	*find_free_block(size_t size, t_size_type block_type)
{
	t_block	*block;
	t_zone	*zone;

	zone = g_alloc_start;
	while (zone)
	{
		if (zone->type == block_type
		&& (get_zone_total_size(zone->type) - zone->size) >= size)
		{
			block = zone->block_lst;
			while (block)
			{
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
	// ft_printf("Rounded block size %zu\n", size);
	if ((block_type = get_block_type(size)) == LARGE)
		new_zone = create_zone(size);
	else if (!g_alloc_start
	|| !(alloc_block = find_free_block(size, block_type)))
		new_zone = create_zone(get_zone_total_size(block_type) + META_ZONE_SIZE);
	if (new_zone)
		alloc_block = alloc_new_block(new_zone, new_zone->block_lst, size);
	if (!alloc_block)
		return (NULL);
	return ((void*)alloc_block + META_BLOCK_SIZE);
}
