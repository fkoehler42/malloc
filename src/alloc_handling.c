/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 17:48:00 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/12 18:34:34 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*get_free_block(t_zone *zone, size_t block_size)
{
	t_block	*block;

	block = zone->block_lst;
	while (block)
	{
		if (block->is_free && block->size >= block_size)
			return (block);
		block = block->next;
	}
	return (NULL);
}

t_block			*find_free_block(size_t block_size, t_size_type block_type)
{
	t_block	*free_block;
	t_zone	*zone;

	free_block = NULL;
	zone = g_alloc_start;
	while (zone)
	{
		if (zone->type == block_type)
		{
			if (((get_zone_type_size(zone->type) - zone->size) >= block_size)
			&& (free_block = get_free_block(zone, block_size)))
				return (free_block);
		}
		zone = zone->next;
	}
	return (NULL);
}

void			*get_allocated_ptr(size_t block_size)
{
	t_size_type	block_type;
	t_block		*free_block;
	t_zone		*new;

	free_block = NULL;
	new = NULL;
	block_size = get_rounded_block_size(block_size);
	ft_printf("Rounded block size %zu\n", block_size);
	if ((block_type = get_block_type(block_size)) == LARGE)
		new = create_alloc_zone(block_size);
	else
	{
		if (!(free_block = find_free_block(block_size, block_type)))
			new = create_alloc_zone(get_zone_type_size(block_type));
	}
	if (new)return (NULL);
	else if (!free_block)
		return (NULL);
	return (free_block + META_BLOCK_SIZE);
}
