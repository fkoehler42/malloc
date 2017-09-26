/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 12:32:30 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/26 18:22:13 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		ft_free(void *ptr)
{
	t_zone	*zone;

	if (ptr != NULL && (zone = get_ptr_zone(ptr)) != NULL)
	{
		// ft_printf("\nfree called on ptr %p, found in range of zone %p !\n", ptr, zone);
		if (deallocate_ptr(ptr, zone) == -1){
			//print error msg and raise a SIGABORT
			ft_printf("\nError in deallocation process\n");
			exit(1);
		}
	}
}

void		*ft_realloc(void *ptr, size_t size)
{
	t_zone	*zone;
	void 	*new_ptr;

	if (!ptr)
		return (ft_malloc(size));
	if (size == 0)
	{
		ft_free(ptr);
		return (ft_malloc(1));
	}
	if ((zone = get_ptr_zone(ptr)) != NULL
	&& is_valid_block((t_block*)(ptr - META_BLOCK_SIZE), zone))
	{
		new_ptr = realloc_process(ptr, size, zone);
		if (new_ptr != NULL && new_ptr != ptr)
			deallocate_ptr(ptr, zone);
		return (new_ptr);
	}
	return (NULL);
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
	{
		put_alloc_error(ALLOC_OVERSIZED, size);
		return (NULL);
	}
	// ft_printf("\n/// ft_malloc debug \\\\\\\nMETA_BLOCK_SIZE : %zu\nMETA_ZONE_SIZE : %zu\nMAX_ALLOC_SIZE : %zu\n", META_BLOCK_SIZE, META_ZONE_SIZE, MAX_ALLOC_SIZE);
	return (get_allocated_ptr(size));
}
