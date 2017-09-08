/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flav <flav@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 17:22:05 by flav              #+#    #+#             */
/*   Updated: 2017/09/08 18:21:06 by flav             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_size_type	get_zone_type(size_t size)
{
	if (size == TINY_SIZE)
		return (TINY);
	else if (size == SMALL_SIZE)
		return (SMALL);
	else
		return (LARGE);
}

size_t		get_zone_size(t_zone *zone)
{
	if (zone->type == TINY)
		return (TINY_SIZE);
	else if (zone->type == SMALL)
		return (SMALL_SIZE);
	else
		return (zone->size);
}

t_size_type	get_block_type(size_t size)
{
	if (size <= TINY_MAX_ALLOC)
		return (TINY);
	else if (size <= SMALL_MAX_ALLOC)
		return (SMALL);
	else
		return (LARGE);
}
