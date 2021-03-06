/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:14:40 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/09 15:14:13 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*get_dup_block_ptr(t_block *block, size_t size, size_t old_size)
{
	void	*ptr;
	size_t	size_to_copy;

	if (!(ptr = get_allocated_ptr(size)))
		return (NULL);
	size_to_copy = size > old_size ? old_size : size;
	ft_memcpy(ptr, ((void*)block + META_BLOCK_SIZE), size_to_copy);
	return (ptr);
}

t_block		*reduce_block(t_block *block, size_t size, size_t *zone_size)
{
	split_block(block, size);
	*zone_size = *zone_size + META_BLOCK_SIZE - block->next->size;
	block->next->is_free = 1;
	merge_contiguous_blocks(block->next, zone_size);
	return (block);
}

t_block		*enlarge_block(t_block *block, size_t size, size_t *zone_size,
size_t min_block_size)
{
	t_block	*tmp;

	tmp = block;
	while (block->size < size && tmp->next && tmp->next->is_free)
	{
		tmp = tmp->next;
		block->size += (tmp->size + META_BLOCK_SIZE);
		*zone_size += tmp->size;
		check_data_validity((void*)tmp, BLOCK);
	}
	if (block == tmp)
		return (NULL);
	block->next = tmp->next;
	if (block->next)
		block->next->prev = block;
	if (block->size < size)
		return (NULL);
	if (block->size >= size + min_block_size)
	{
		split_block(block, size);
		*zone_size = *zone_size + META_BLOCK_SIZE - block->next->size;
		block->next->is_free = 1;
	}
	return (block);
}

t_block		*split_block(t_block *block, size_t size)
{
	t_block	*split;

	split = (t_block*)ft_memcpy((void*)block + META_BLOCK_SIZE + size,
	(void*)block, META_ZONE_SIZE);
	split->size -= (size + META_BLOCK_SIZE);
	split->canary = CANARY(split->canary);
	split->prev = block;
	block->size = size;
	block->next = split;
	return (block);
}

void		merge_contiguous_blocks(t_block *block, size_t *zone_size)
{
	while (block->prev && block->prev->is_free)
	{
		check_data_validity((void*)block->prev, BLOCK);
		block = block->prev;
	}
	while (block->next && block->next->is_free)
	{
		check_data_validity((void*)block->next, BLOCK);
		block->size += block->next->size + META_BLOCK_SIZE;
		block->next = block->next->next;
		*zone_size -= META_BLOCK_SIZE;
	}
}
