/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 12:32:30 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/07 19:55:25 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"
#include <sys/mman.h>

t_zone				*create_alloc_zone(t_zone **zone_lst, int zone_type, size_t zone_size)
{
	t_zone	*new;
	t_zone	*tmp;

	if ((new = mmap(0, zone_size, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	ft_printf("Address allocated : %x, size : %zu\n", new, zone_size);
	new->size_type = zone_type;
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

static t_zones_tree	*init_alloc_zones(void)
{
	t_zones_tree	*zones_tree;

	if ((zones_tree = mmap(0, sizeof(*zones_tree), PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	zones_tree->tiny_lst = NULL;
	zones_tree->small_lst = NULL;
	zones_tree->large_lst = NULL;
	if (!(create_alloc_zone(&zones_tree->tiny_lst, TINY, TINY_ZONE_SIZE)))
		return (NULL);
	if (!(create_alloc_zone(&zones_tree->small_lst, SMALL, SMALL_ZONE_SIZE)))
		return (NULL);
	return (zones_tree);
}

void				*ft_malloc(size_t size)
{
	static 	t_zones_tree *zones_tree = NULL;
	t_block	*alloc_block;

	ft_printf("ft_malloc called for %zu bytes\n", size);
	if (!zones_tree && !(zones_tree = init_alloc_zones()))
		return (NULL);
	return ((void*)42);
}
