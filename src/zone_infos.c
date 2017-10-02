/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_infos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 17:22:05 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/02 17:11:15 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_size_type	get_zone_type(size_t size)
{
	if (size == (size_t)TINY_SIZE)
		return (TINY);
	else if (size == (size_t)SMALL_SIZE)
		return (SMALL);
	else
		return (LARGE);
}
