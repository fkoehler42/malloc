/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:14:40 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/22 18:13:19 by flav             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
	// ft_printf("<-- split block -->\nfree : %p\nnew : %p, canary : %p\n", split, block, block->canary);
	return (block);
}

int			merge_contiguous_blocks(t_block *block, size_t *zone_size)
{
	while (block->prev && block->prev->is_free)
	{
		if (!is_data_valid((void*)block->prev, BLOCK))
			return (-1);
		block = block->prev;
	}
	while (block->next && block->next->is_free)
	{
		if (!is_data_valid((void*)block->next, BLOCK))
			return (-1);
		// ft_printf("\nnext block : %p, is free : %d, size : %zu\n", block->next, block->next->is_free, block->next->size);
		block->size += block->next->size + META_BLOCK_SIZE;
		block->next = block->next->next;
		*zone_size += META_BLOCK_SIZE;
	}
	return (0);
}
