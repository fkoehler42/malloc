/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 17:48:00 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/08 18:31:18 by flav             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*find_free_block_in_zone(t_zone *zone, size_t block_size)
{
	t_block	*block;

	if (!block = zone->block_lst)
		//create first bloc of zone;
	while (block->next && (!block->is_free || block->size < block_size))
		block = block->next;
}

void 			find_free_block(t_zone *zone, size_t block_size,
t_size_type block_type)
{
	t_block	*free_block;

	while (zone)
	{
		if (zone->type == block_type
			&& ((get_zone_size(zone) - zone->size) >= block_size))
			free_block = find_free_block_in_zone(zone, block_size);
	}
}

t_block			*get_allocated_ptr(t_zone *begin, size_t block_size)
{
	t_size_type	block_type;

	block_type = get_block_type(block_size);
	find_free_block(begin, block_size, block_type);

	begin++;
	return (NULL);
}
