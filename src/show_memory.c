/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 21:20:14 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/21 21:20:46 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		show_alloc_mem()
{
	t_zone 	*zone;
	t_block	*block;
	void	*block_start;
	void	*block_end;

	zone = g_alloc_start;
	while (zone)
	{
		ft_printf("%s%s%s : %p\n", PURPLE, get_zone_type_str(zone->type), OFF, zone);
		block = zone->block_lst;
		while (block)
		{
			if (!block->is_free)
			{
				block_start = (void*)block + META_BLOCK_SIZE;
				block_end = (void*)block + META_BLOCK_SIZE + block->size - 1;
				ft_printf("%p - %p : %zu bytes\n", block_start, block_end, block->size);
			}
			block = block->next;
		}
		zone = zone->next;
	}
}
