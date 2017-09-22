/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 21:20:14 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/22 14:47:20 by flav             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	show_alloc_zone(t_zone *zone)
{
	size_t	total_size;
	t_block	*block;
	void	*block_start;
	void	*block_end;

	total_size = 0;
	block = zone->block_lst;
	while (block)
	{
		if (!block->is_free)
		{
			block_start = (void*)block + META_BLOCK_SIZE;
			block_end = (void*)block + META_BLOCK_SIZE + block->size - 1;
			ft_printf("%p - %p : %zu bytes\n", block_start, block_end, block->size);
			total_size += block->size;
		}
		block = block->next;
	}
	return (total_size);
}

void			show_alloc_mem(void)
{
	size_t	total_size;
	t_zone 	*zone;

	total_size = 0;
	zone = g_alloc_start;
	while (zone)
	{
		ft_printf("%s%-5s%s : %p\n", PURPLE, get_zone_type_str(zone->type), OFF, zone);
		total_size += show_alloc_zone(zone);
		zone = zone->next;
	}
	ft_printf("%sTOTAL%s : %zu bytes\n", GREEN, OFF, total_size);
}
