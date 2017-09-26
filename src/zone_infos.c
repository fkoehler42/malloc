/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_infos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 17:22:05 by fkoehler          #+#    #+#             */
/*   Updated: 2017/09/26 17:00:34 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

char		*get_zone_type_str(t_size_type type)
{
	if (type == TINY)
	return ("TINY");
	else if (type == SMALL)
		return ("SMALL");
	else
		return ("LARGE");
}

t_size_type	get_zone_type(size_t size)
{
	if (size == TINY_SIZE)
		return (TINY);
	else if (size == SMALL_SIZE)
		return (SMALL);
	else
		return (LARGE);
}
