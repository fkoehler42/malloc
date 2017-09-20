/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:14:40 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/20 19:44:25 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block		*split_and_add_block(t_block *block, size_t size)
{
	t_block	*new;

	block->size -= (size + META_BLOCK_SIZE);
	new = (t_block*)((void*)block + META_BLOCK_SIZE + block->size);
	// ft_printf("<-- split block -->\nfree : %p\nnew : %p\n", block, new);
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
		block = block->prev;
	if (block->prev && block->prev->is_free != 0)
		return (-1);
	while (block->next && (block->next->is_free == 1))
	{
		// ft_printf("\nnext block : %p, is free : %d, size : %zu\n", block->next, block->next->is_free, block->next->size);
		block->size += block->next->size + META_BLOCK_SIZE;
		block->next = block->next->next;
		*zone_size += META_BLOCK_SIZE;
	}
	if (block->next && block->next->is_free != 0)
		return (-1);
	return (0);
}
