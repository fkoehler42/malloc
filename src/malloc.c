/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 12:32:30 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/03 13:11:24 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		free_unsafe(void *ptr)
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

void		*realloc_unsafe(void *ptr, size_t size, int free)
{
	t_zone	*zone;
	void	*new_ptr;

	new_ptr = NULL;
	if (!ptr)
		return (malloc_unsafe(size));
	if (size == 0)
	{
		free_unsafe(ptr);
		return (malloc_unsafe(1));
	}
	if ((zone = get_ptr_zone(ptr)) != NULL
	&& is_valid_block((t_block*)(ptr - META_BLOCK_SIZE), zone))
	{
		new_ptr = realloc_process(ptr, size, zone);
		if ((new_ptr != NULL && new_ptr != ptr) || (!new_ptr && free == 1))
			deallocate_ptr(ptr, zone);
	}
	else if (!zone && ERROR_OUT_OF_RANGE)
		put_error(NOT_ALLOCATED, ptr);
	return (new_ptr);
}

void		*calloc_unsafe(size_t count, size_t size)
{
	void	*ptr;
	size_t	length;

	length = count * size;
	if (!(ptr = malloc_unsafe(length)))
		return (NULL);
	return (ft_memset(ptr, 0, length));
}

void		*malloc_unsafe(size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (size == 0)
		size++;
	if (size > MAX_ALLOC_SIZE)
		put_alloc_error(ALLOC_OVERSIZED, size);
	else
		ptr = get_allocated_ptr(size);
	return (ptr);
}
