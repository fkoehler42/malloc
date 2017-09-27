/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 12:32:30 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/27 18:56:34 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		free(void *ptr)
{
	t_zone	*zone;

	if (ptr != NULL)
	{
		if ((zone = get_ptr_zone(ptr)) != NULL)
		{
			if (deallocate_ptr(ptr, zone) == -1)
				put_error(NOT_ALLOCATED, ptr);
		}
		else if (ERROR_OUT_OF_RANGE)
			put_error(NOT_ALLOCATED, ptr);
	}
}

void		*realloc(void *ptr, size_t size)
{
	t_zone	*zone;
	void 	*new_ptr;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (malloc(1));
	}
	if ((zone = get_ptr_zone(ptr)) != NULL
	&& is_valid_block((t_block*)(ptr - META_BLOCK_SIZE), zone))
	{
		new_ptr = realloc_process(ptr, size, zone);
		if (new_ptr != NULL && new_ptr != ptr)
			deallocate_ptr(ptr, zone);
		return (new_ptr);
	}
	else if (!zone && ERROR_OUT_OF_RANGE)
		put_error(NOT_ALLOCATED, ptr);
	return (NULL);
}

void		*calloc(size_t count, size_t size)
{
	void 	*ptr;
	size_t	length;

	length = count * size;
	if (!(ptr = malloc(length)))
		return (NULL);
	return (ft_memset(ptr, 0, length));
}

void		*malloc(size_t size)
{
	if (size == 0)
		size++;
	if (size > MAX_ALLOC_SIZE)
	{
		put_alloc_error(ALLOC_OVERSIZED, size);
		return (NULL);
	}
	// ft_printf("\n/// ft_malloc debug \\\\\\\nMETA_BLOCK_SIZE : %zu\nMETA_ZONE_SIZE : %zu\nMAX_ALLOC_SIZE : %zu\n", META_BLOCK_SIZE, META_ZONE_SIZE, MAX_ALLOC_SIZE);
	return (get_allocated_ptr(size));
}
