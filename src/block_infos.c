/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 17:22:05 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/25 16:46:20 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_size_type	get_block_type(size_t size)
{
	if (size <= TINY_MAX_ALLOC)
		return (TINY);
	else if (size <= SMALL_MAX_ALLOC)
		return (SMALL);
	else
		return (LARGE);
}

/*
** Block metadata included
*/
size_t		get_min_block_size(t_size_type type)
{
	size_t	min_alloc;

	if (type == TINY)
		min_alloc = 1;
	else if (type == SMALL)
		min_alloc = TINY_MAX_ALLOC + 1;
	else
		min_alloc = SMALL_MAX_ALLOC + 1;
	return (get_rounded_block_size(min_alloc) + META_BLOCK_SIZE);
}

size_t		get_rounded_block_size(size_t size)
{
	size_t	alloc_resolution;
	size_t	modulo;
	int		metadata_size;

	metadata_size = META_BLOCK_SIZE;
	if (size <= TINY_MAX_ALLOC)
		alloc_resolution = TINY_RESOLUTION;
	else if (size <= SMALL_MAX_ALLOC)
		alloc_resolution = SMALL_RESOLUTION;
	else
	{
		alloc_resolution = LARGE_RESOLUTION;
		metadata_size += META_ZONE_SIZE;
	}
	if ((modulo = (size + metadata_size) % alloc_resolution) > 0)
		size = size + alloc_resolution - modulo;
	return (size);
}
