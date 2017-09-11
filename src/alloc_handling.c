/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 17:48:00 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/11 15:07:21 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	create_new_block(t_zone **zone, size_t size)
{
	t_block	*new;

	new->size = size;
	new->is_free = 0;
	if (!((*zone)->block_lst)))

}

static t_block	*find_free_block_in_zone(t_zone *zone, size_t block_size)
{
	t_block	*block;

	if (!(block = zone->block_lst))
		//create first bloc of zone;
	while (block->next && (!block->is_free || block->size < block_size))
		block = block->next;
}

void 			find_free_block(t_zone *zone, size_t block_size,
t_size_type block_type)
{
	t_block	*free_block;

	free_block = NULL;
	while (zone)
	{
		if (zone->type == block_type
			&& ((get_zone_size(zone->type) - zone->size) >= block_size))
		{
			if (free_block = find_free_block_in_zone(zone, block_size))
				return (free_block);
		}
		zone = zone->next;
	}
	return (NULL);
}

t_block			*get_allocated_ptr(t_zone *begin, size_t block_size)
{
	t_size_type	block_type;
	t_block		*free_block;
	t_zone		*new;

	free_block = NULL;
	new = NULL;
	block_size = get_rounded_block_size(block_size + META_BLOCK_SIZE);
	if ((block_type = get_block_type(block_size)) == LARGE)
		new = create_alloc_zone(&begin, block_size);
	else
	{
		if (!(free_block = find_free_block(begin, block_size, block_type))
			new = create_alloc_zone(&begin, get_zone_size(block_type));
	}
	if (new)
		free_block = create_new_block(&new, block_size);
	else if (!free_block)
		return (NULL)
	return (free_block + META_BLOCK_SIZE);
}
