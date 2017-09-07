/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_zones_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 17:48:00 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/07 19:55:50 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_malloc.h"

int		get_zone_type(size_t size)
{
	if (size <= TINY_BLOCK_MAX_SIZE)
		return (TINY);
	else if (size <= SMALL_BLOCK_MAX_SIZE)
		return (SMALL);
	else
		return (LARGE);
}
