/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 12:32:30 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/14 15:57:20 by flav             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void				*ft_malloc(size_t size)
{
	void			*ptr;

	if (size == 0)
		size++;
	if (size > MAX_ALLOC_SIZE)
		return (NULL);
	// ft_printf("\n/// ft_malloc debug \\\\\\\nMETA_BLOCK_SIZE : %zu\nMETA_ZONE_SIZE : %zu\nMAX_ALLOC_SIZE : %zu\n", META_BLOCK_SIZE, META_ZONE_SIZE, MAX_ALLOC_SIZE);
	if (!g_alloc_start)
	{
		if (!(create_zone(TINY_SIZE)))
			return (NULL);
		if (!(create_zone(SMALL_SIZE)))
			return (NULL);
	}
	ptr = get_allocated_ptr(size);
	return (ptr);
}
