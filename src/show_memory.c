/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 21:20:14 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/02 17:31:38 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		show_block_infos(t_block *block, t_block_state block_state)
{
	void	*block_start;
	void	*block_end;

	block_start = (void*)block + META_BLOCK_SIZE;
	block_end = block_start + block->size - 1;

	if (block_state == ALL)
	{
		if (block->is_free)
			write(1, GREEN"F"OFF" ", ft_strlen(GREEN""OFF) + 2);
		else
			write(1, RED"A"OFF" ", ft_strlen(RED""OFF) + 2);
	}
	ft_putstr("0x");
	ft_put_uintmax((size_t)block_start, 16);
	ft_putstr(" - 0x");
	ft_put_uintmax((size_t)block_end, 16);
	ft_putstr(" : ");
	ft_put_uintmax(block->size, 10);
	ft_putstr(" bytes\n");
}

static size_t	show_blocks(t_zone *zone, t_block_state block_state)
{
	size_t	total_size;
	t_block	*block;

	total_size = 0;
	block = zone->block_lst;
	while (block)
	{
		check_data_validity((void*)block, BLOCK);
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
	zone = g_alloc.heap;
	while (zone)
	{
		check_data_validity((void*)zone, ZONE);
		ft_putstr(PURPLE);
		if (zone->type == TINY)
			write(1, "TINY "OFF" : 0x", ft_strlen(OFF) + 10);
		else if (zone->type == SMALL)
			write(1, "SMALL"OFF" : 0x", ft_strlen(OFF) + 10);
		else if (zone->type == LARGE)
			write(1, "LARGE"OFF" : 0x", ft_strlen(OFF) + 10);
		ft_put_uintmax((size_t)zone, 16);
		ft_putchar('\n');
		total_size += show_blocks(zone, block_state);
		zone = zone->next;
	}
	write(1, PURPLE"TOTAL"OFF" : ", ft_strlen(PURPLE""OFF) + 8);
	ft_put_uintmax(total_size, 10);
	ft_putstr(" bytes\n");
}

void			show_alloc_mem(void)
{
	if (!g_alloc.locker_init)
		init_locker();
	pthread_mutex_lock(&g_alloc.locker);
	show_zones(ALLOC);
	pthread_mutex_unlock(&g_alloc.locker);
}

void			show_mem(t_block_state block_state)
{
	if (!g_alloc.locker_init)
		init_locker();
	pthread_mutex_lock(&g_alloc.locker);
	show_zones(block_state);
	pthread_mutex_unlock(&g_alloc.locker);
}
