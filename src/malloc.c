/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 12:32:30 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/19 17:26:31 by fkoehler         ###   ########.fr       */
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

void		ft_free(void *ptr)
{
	t_zone	*zone;

	if (ptr != NULL && (zone = get_ptr_zone(ptr)) != NULL)
	{
		// ft_printf("\nfree called on ptr %p, found in range of zone %p !\n", ptr, zone);
		if (deallocate_ptr(ptr, zone) == -1){}
			//print error msg
	}
	else;
		//print error msg
}

void		*ft_calloc(size_t count, size_t size)
{
	void 	*ptr;
	size_t	length;

	length = count * size;
	if (!(ptr = ft_malloc(length)))
		return (NULL);
	return (ft_memset(ptr, 0, length));
}

void		*ft_malloc(size_t size)
{
	if (size == 0)
		size++;
	if (size > MAX_ALLOC_SIZE)
		return (NULL);
	// ft_printf("\n/// ft_malloc debug \\\\\\\nMETA_BLOCK_SIZE : %zu\nMETA_ZONE_SIZE : %zu\nMAX_ALLOC_SIZE : %zu\n", META_BLOCK_SIZE, META_ZONE_SIZE, MAX_ALLOC_SIZE);
	return (get_allocated_ptr(size));
}
