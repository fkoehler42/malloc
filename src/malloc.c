/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 12:32:30 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/11 13:29:58 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/mman.h>

t_zone					*create_alloc_zone(t_zone **zone_lst, size_t size)
{
	t_zone	*new;
	t_zone	*tmp;

	if ((new = mmap(0, size + META_ZONE_SIZE, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	ft_printf("Address allocated : %x, size : %zu\n", new, size);
	new->type = get_zone_type(size);
	new->size = 0;
	new->block_lst = NULL;
	new->next = NULL;
	if ((tmp = *zone_lst) != NULL)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*zone_lst = new;
	return (new);
}

void				*ft_malloc(size_t size)
{
	static t_zone	*begin = NULL;
	void			*ptr;

	ft_printf("ft_malloc called for %zu bytes\nMETA_SIZE : %zu\nMAX_ALLOC_SIZE : to define..\n", size, META_SIZE);
	if (!begin)
	{
		if (!(create_alloc_zone(&begin, TINY_SIZE)))
			return (NULL);
		if (!(create_alloc_zone(&begin, SMALL_SIZE)))
			return (NULL);
	}
	ptr = get_allocated_ptr(begin, size);
	return ((void*)free_block);
}
