/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deallocation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:17:23 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/18 16:12:24 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	is_valid_block(t_block *block, t_zone *zone)
{
	t_block *tmp;

	if (!(tmp = zone->block_lst))
		return (0);
	while (tmp)
	{
		if (block == tmp && !block->is_free)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_zone		*get_ptr_zone(void *ptr)
{
	t_zone	*zone;
	void 	*zone_end;

	if ((zone = g_alloc_start))
	{
		while (zone)
		{
			zone_end = (void*)zone + get_zone_total_size(zone->type)
			+ META_ZONE_SIZE - 1;
			if (ptr > (void*)zone && ptr < zone_end)
				return (zone);
			zone = zone->next;
		}
	}
	return (NULL);
}

int		deallocate_ptr(void *ptr, t_zone *zone)
{
	t_block	*block;

	block = (t_block*)(ptr - META_BLOCK_SIZE);
	if (!is_valid_block(block, zone))
		return (-1);
	block->is_free = 1;
	zone->size -= block->size;
	merge_contiguous_blocks(block, &zone->size);
	if (!(zone->block_lst->next))
		delete_zone(zone);
	return (0);
}
