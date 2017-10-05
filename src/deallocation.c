/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deallocation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:17:23 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/05 14:45:13 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	is_zone_free(t_zone *zone)
{
	if (zone->block_lst->is_free && !zone->block_lst->next)
		return (1);
	return (0);
}

static int	count_free_zones(t_size_type type)
{
	int		i;
	t_zone	*zone;

	i = 0;
	zone = g_alloc.heap;
	while (zone)
	{
		if ((!type || zone->type == type) && is_zone_free(zone))
			i++;
		zone = zone->next;
	}
	return (i);
}

int			is_valid_block(t_block *block, t_zone *zone)
{
	t_block *tmp;

	if (!(tmp = zone->block_lst))
		put_error(NOT_ALLOCATED, block);
	while (tmp)
	{
		check_data_validity((void*)tmp, BLOCK);
		// ft_printf("\nblock data address : %p\n", (void*)tmp + META_BLOCK_SIZE);
		if (tmp == block)
		{
			if (tmp->is_free)
				put_error(NOT_ALLOCATED, block);
			return (1);
		}
		tmp = tmp->next;
	}
	put_error(NOT_ALLOCATED, block);
	return (0);
}

t_zone		*get_ptr_zone(void *ptr)
{
	t_zone	*zone;
	void	*zone_end;
	size_t	total_zone_size;

	if ((zone = g_alloc.heap))
	{
		while (zone)
		{
			check_data_validity((void*)zone, ZONE);
			if (zone->type == LARGE)
				zone_end = (void*)zone + zone->size - 1;
			else
			{
				total_zone_size = (zone->type == TINY) ? TINY_SIZE : SMALL_SIZE;
				zone_end = (void*)zone + total_zone_size - 1;
			}
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
	if (zone->type == LARGE)
		delete_zone(zone);
	else
	{
		block->is_free = 1;
		zone->size -= block->size;
		merge_contiguous_blocks(block, &zone->size);
		if (is_zone_free(zone) && count_free_zones(zone->type) > 1)
			delete_zone(zone);
	}
	return (0);
}
