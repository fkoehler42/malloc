/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:14:40 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/21 18:42:58 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block		*split_and_add_block(t_block *block, size_t size)
{
	t_block	*new;

	block->size -= (size + META_BLOCK_SIZE);
	new = (t_block*)((void*)block + META_BLOCK_SIZE + block->size);
	new->canary = CANARY(new->canary);
	// ft_printf("<-- split block -->\nfree : %p\nnew : %p, canary : %p\n", block, new, new->canary);
	new->size = size;
	new->is_free = 1;
	new->prev = block;
	new->next = block->next;
	block->next = new;
	return (new);
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
