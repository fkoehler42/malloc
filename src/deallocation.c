/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deallocation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:17:23 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/25 12:53:00 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int			is_valid_block(t_block *block, t_zone *zone)
{
	t_block *tmp;

	if (!(tmp = zone->block_lst))
		return (0);
	while (tmp)
	{
		if (!is_data_valid((void*)tmp, BLOCK))
			return (0);
		// ft_printf("\nblock data address : %p\n", (void*)tmp + META_BLOCK_SIZE);
		if (tmp == block)
			return (tmp->is_free ? 0 : 1);
		tmp = tmp->next;
	}
	return (0);
}

t_zone		*get_ptr_zone(void *ptr)
{
	t_zone	*zone;
	void	*zone_end;

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

int			deallocate_ptr(void *ptr, t_zone *zone)
{
	t_block	*block;

	block = (t_block*)(ptr - META_BLOCK_SIZE);
	if (!is_valid_block(block, zone))
		return (-1);
	block->is_free = 1;
	zone->size -= block->size;
	if (merge_contiguous_blocks(block, &zone->size) < 0)
		return (-1);
	if (!(zone->block_lst->next))
		delete_zone(zone);
	return (0);
}
