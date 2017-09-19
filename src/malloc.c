/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 12:32:30 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/19 11:26:20 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void 		ft_free(void *ptr)
{
	t_zone	*zone;

	if (ptr != NULL && (zone = get_ptr_zone(ptr)) != NULL)
	{
		// ft_printf("\nfree called on ptr %p, found in range of zone %p !\n", ptr, zone);
		if (deallocate_ptr(ptr, zone) == -1){}
			//print error msg
	}
	else;
		//print error msg
}

void		*ft_malloc(size_t size)
{
	if (size == 0)
		size++;
	if (size > MAX_ALLOC_SIZE)
		return (NULL);
	// ft_printf("\n/// ft_malloc debug \\\\\\\nMETA_BLOCK_SIZE : %zu\nMETA_ZONE_SIZE : %zu\nMAX_ALLOC_SIZE : %zu\n", META_BLOCK_SIZE, META_ZONE_SIZE, MAX_ALLOC_SIZE);
	return (get_allocated_ptr(size));
}
