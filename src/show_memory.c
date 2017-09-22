/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 21:20:14 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/22 17:00:32 by flav             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		show_block_infos(t_block *block, t_block_state block_state)
{
	void	*block_start;
	void	*block_end;
	char	state;
	char	*state_color;

	block_start = (void*)block + META_BLOCK_SIZE;
	block_end = block_start + block->size - 1;

	if (block_state == ALL)
	{
		state = block->is_free ? 'F' : 'A';
		state_color = block->is_free ? GREEN : RED;
		ft_printf("%s%c%s %p - %p : %zu bytes\n",
		state_color, state, OFF, block_start, block_end, block->size);
	}
	else
		ft_printf("%p - %p : %zu bytes\n", block_start, block_end, block->size);

}

static size_t	show_blocks(t_zone *zone, t_block_state block_state)
{
	size_t	total_size;
	t_block	*block;

	total_size = 0;
	block = zone->block_lst;
	while (block)
	{
		if ((block_state == ALLOC && block->is_free)
		|| (block_state == FREE && !block->is_free))
		{
			block = block->next;
			continue;
		}
		show_block_infos(block, block_state);
		total_size += block->size;
		block = block->next;
	}
	return (total_size);
}

static void		show_zones(t_block_state block_state)
{
	size_t	total_size;
	t_zone 	*zone;

	total_size = 0;
	zone = g_alloc_start;
	while (zone)
	{
		ft_printf("%s%-5s%s : %p\n", PURPLE, get_zone_type_str(zone->type), OFF, zone);
		total_size += show_blocks(zone, block_state);
		zone = zone->next;
	}
	ft_printf("%sTOTAL%s : %zu bytes\n", PURPLE, OFF, total_size);
}

void			show_alloc_mem(void)
{
	show_zones(ALLOC);
}

void			show_mem(t_block_state block_state)
{
	show_zones(block_state);
}
