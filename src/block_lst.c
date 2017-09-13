/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:14:40 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/13 21:51:19 by flav             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block		*split_and_add_block(t_block *block, size_t size)
{
	t_block	*new;

	block->size -= (size + META_BLOCK_SIZE);
	new = (t_block*)((void*)block + META_BLOCK_SIZE + block->size + 1);
	ft_printf("<-- split block -->\n1 : %p\n2 : %p\n", block, new);
	new->size = size;
	new->is_free = 1;
	new->prev = block;
	new->next = block->next;
	block->next = new;
	return (new);
}
