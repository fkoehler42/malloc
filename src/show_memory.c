/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 21:20:14 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/09 15:38:59 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		show_block_infos(t_block *block, t_display_flag display_flag)
{
	void	*block_start;
	void	*block_end;

	block_start = (void*)block + META_BLOCK_SIZE;
	block_end = block_start + block->size - 1;
	if (display_flag == ALL)
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
	if (display_flag == DUMP)
		show_mem_dump(block_start, block->size);
}

static size_t	show_blocks(t_zone *zone, t_display_flag display_flag)
{
	size_t	total_size;
	t_block	*block;

	total_size = 0;
	block = zone->block_lst;
	while (block)
	{
		check_data_validity((void*)block, BLOCK);
		if (((display_flag == ALLOC || display_flag == DUMP) && !block->is_free)
		|| (display_flag == FREE && block->is_free) || display_flag == ALL)
		{
			show_block_infos(block, display_flag);
			total_size += block->size;
		}
		block = block->next;
	}
	return (total_size);
}

static void		show_zones(t_display_flag display_flag)
{
	size_t	total_size;
	t_zone	*zone;

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
		total_size += show_blocks(zone, display_flag);
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

void			show_mem(t_display_flag display_flag)
{
	if (!g_alloc.locker_init)
		init_locker();
	pthread_mutex_lock(&g_alloc.locker);
	show_zones(display_flag);
	pthread_mutex_unlock(&g_alloc.locker);
}
